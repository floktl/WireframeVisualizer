/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/20 11:49:59 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to fork the process to execute the python script and open the pipes
int	redirect_pipe_execute_python_script(t_win_data *window)
{
	int		i;

	window->python_pid = fork();
	if (window->python_pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	else if (window->python_pid == 0)
	{
		i = 0;
		ft_printf("\n\033[0;35mRedirecting pipes...\033[0m\n");
		while (i < 4)
		{
			close(window->thread_data[i].pipe_fd[1]);
			dup2(window->thread_data[i].pipe_fd[0], i + 3);
			ft_printf("end of Pipe %i redirected to fd %i\n", i, i + 3);
			i++;
		}
		ft_printf("\n\033[0;35mExecuting the Python script\033[0m\n");
		execlp("python3", "python3",
			"src/python_data/python_files/visualize_struct.py", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// function to create the pipes and start the Python script for visual data
int	create_pipe(t_win_data *window)
{
	int		i;

	window->threads = malloc(sizeof(pthread_t) * 4);
	if (!window->threads)
		return (perror("malloc threads"), EXIT_FAILURE);
	window->thread_data = malloc(sizeof(t_pipe_thread_data) * 4);
	if (!window->thread_data)
		return (perror("malloc thread_data"), EXIT_FAILURE);
	ft_printf("\n\033[0;35mCreating pipes...\033[0m\n");
	i = 0;
	while (i < 4)
	{
		window->thread_data[i].pipe_fd[0] = -1;
		window->thread_data[i].pipe_fd[1] = -1;
		if (pipe(window->thread_data[i].pipe_fd) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		ft_printf("\033[0;34mPipe %d:\033[0m read fd = %d, write fd = %d\n",
			i, window->thread_data[i].pipe_fd[0],
			window->thread_data[i].pipe_fd[1]);
		if (i == 0)
		{
			window->thread_data[i++].write_size = 3 * sizeof(int);
		}
		else if (i == 1)
			window->thread_data[i++].write_size = 2 * sizeof(int);
		else if (i == 2)
			window->thread_data[i++].write_size = 2 * sizeof(int);
		else if (i == 3)
			window->thread_data[i++].write_size = sizeof(int);
	}
	if (redirect_pipe_execute_python_script(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
		if (close(window->thread_data[i++].pipe_fd[0]) == -1)
			return (perror("close read fd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//	function to store the data values inside buffer and write it to pipe
int	write_data_in_buf(t_pipe_thread_data *data, ssize_t *bytes_written)
{
	if (data->pipe_index < 0 || data->pipe_index > 3)
		return (-1);
	pthread_mutex_lock(&data->data_mutex);
	*bytes_written = write(data->pipe_fd[1], data->data_buf, data->write_size);
	if (*bytes_written != data->write_size || *bytes_written == -1)
		return (pthread_mutex_unlock(&data->data_mutex), -1);
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

//	function to write data values in the struct using a buffer
int	write_into_pipes(t_pipe_thread_data *data)
{
	ssize_t	bytes_written;

	if (data->pipe_fd[1] <= 0)
		return (fprintf(stderr, "Invalid pipe %d\n", data->pipe_fd[1]), -1);
	bytes_written = 0;
	if (write_data_in_buf(data, &bytes_written) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			close(data->pipe_fd[1]);
			data->pipe_fd[1] = -1;
			return (-1);
		}
		else if (bytes_written == -1)
			fprintf(stderr, "Write error on pipe %d: %s\n",
				data->pipe_index, strerror(errno));
		else
			fprintf(stderr, "Partial write on pipe %d: %zd/%zd bytes\n",
				data->pipe_index, bytes_written, data->write_size);
	}
	return (0);
}

//	function to kill the data visualisation script before exiting the c program
void	kill_python_process(pid_t *python_pid)
{
	if (*python_pid > 0)
	{
		if (kill(*python_pid, SIGTERM) == -1)
		{
			perror("Failed to kill Python process");
		}
		else
		{
			ft_printf("Killed Python data-visualization script process!\n");
			*python_pid = -1;
		}
	}
}
