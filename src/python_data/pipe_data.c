/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/18 21:03:31 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to fork the process to execute the python script and open the pipes
int	execute_python_script(t_window *window)
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
			printf("end of Pipe %i redirected to fd %i\n", i, i + 3);
			i++;
		}
		ft_printf("\033[0;35m\nExecuting the Python script\n\033[0m");
		execlp("python3", "python3",
			"src/python_data/python_files/visualize_struct.py", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// function to create the pipes and start the Python script for visual data
int	create_pipe(t_window *window)
{
	int		i;

	i = 0;
	window->threads = malloc(sizeof(pthread_t) * 4);
	if (!window->threads)
		return (perror("malloc threads"), EXIT_FAILURE);
	window->thread_data = malloc(sizeof(t_pipe_thread_data) * 4);
	if (!window->thread_data)
		return (perror("malloc thread_data"), EXIT_FAILURE);
	ft_printf("\n\033[0;35mCreating pipes...\033[0m\n");
	while (i < 4)
	{
		if (pipe(window->thread_data[i].pipe_fd) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		printf("\033[0;34mPipe %d:\033[0m read fd = %d, write fd = %d\n",
			i, window->thread_data[i].pipe_fd[0],
			window->thread_data[i].pipe_fd[1]);
		window->thread_data[i].rot_x = window->map_sz.xm_rot_deg;
		window->thread_data[i].rot_y = window->map_sz.ym_rot_deg;
		window->thread_data[i].rot_z = window->map_sz.zm_rot_deg;
		window->thread_data[i].xposmw = window->map_sz.xposmw;
		window->thread_data[i].yposmw = window->map_sz.yposmw;
		i++;
	}
	if (execute_python_script(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
		close(window->thread_data[i++].pipe_fd[0]);
	return (EXIT_SUCCESS);
}

//	function to write the data in a buffer
int	write_data_in_buf(t_pipe_thread_data *data,
	ssize_t *write_sz, ssize_t *bytes_written)
{
	char	buffer[12];

	int z;
	z = 0;
	if (data->pipe_index == 0)
	{
		pthread_mutex_lock(&data->data_mutex);
		memcpy(buffer, &data->rot_x, sizeof(int));
		memcpy(buffer + sizeof(int), &data->rot_y, sizeof(int));
		memcpy(buffer + 2 * sizeof(int), &data->rot_z, sizeof(int));
		pthread_mutex_unlock(&data->data_mutex);
		*write_sz = 3 * sizeof(int);
	}
	else if (data->pipe_index == 1)
	{
		pthread_mutex_lock(&data->data_mutex);
		memcpy(buffer, &data->xposmw, sizeof(int));
		memcpy(buffer + sizeof(int), &data->yposmw, sizeof(int));
		pthread_mutex_unlock(&data->data_mutex);
		*write_sz = 2 * sizeof(int);
	}
	(void)z;
	*bytes_written = write(data->pipe_fd[1], buffer, *write_sz);
	if (*bytes_written != *write_sz)
		return (-1);
	return (0);
}

//	function to write data values in the struct using a buffer
int	write_into_pipes(t_pipe_thread_data *data)
{
	ssize_t	write_size;
	ssize_t	bytes_written;

	if (data->pipe_fd[1] <= 0)
		return (fprintf(stderr, "Invalid pipe %d\n", data->pipe_fd[1]), -1);
	bytes_written = 0;
	write_size = 0;
	if (write_data_in_buf(data, &write_size, &bytes_written) == -1)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			close(data->pipe_fd[1]);
			data->pipe_fd[1] = -1;
			return (-1);
		}
		if (bytes_written == -1)
			fprintf(stderr, "Write error on pipe %d: %s\n",
				data->pipe_index, strerror(errno));
		else
			fprintf(stderr, "Partial write on pipe %d: %zd/%zd bytes\n",
				data->pipe_index, bytes_written, write_size);
	}
	return (0);
}

//	function to kill the data visualisation script before exiting the c program
void kill_python_process(pid_t *python_pid)
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
