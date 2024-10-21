/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/21 07:24:18 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to print the error on std error output and exits the process
void	exit_and_perror(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

//	function to fork the process to execute the python script and open the pipes
int	redirect_pipe_execute_python_script(t_win_data *window)
{
	int		i;

	window->python_pid = fork();
	if (window->python_pid == -1)
		return (free_threads(window, "python process fork"));
	else if (window->python_pid == 0)
	{
		i = 0;
		ft_printf("\n\033[0;35mRedirecting pipes...\033[0m\n");
		while (i < 4)
		{
			if (close(window->thread_data[i].pipe_fd[1]) == -1)
				exit_and_perror("close write fd");
			if (dup2(window->thread_data[i].pipe_fd[0], i + 3) == -1)
				exit_and_perror("dup2 pipe to fd");
			ft_printf("end of Pipe %i redirected to fd %i\n", i, i + 3);
			i++;
		}
		ft_printf("\n\033[0;35mExecuting the Python script\033[0m\n");
		execlp("python3", "python3",
			"src/python_data/python_files/visualize_struct.py", NULL);
		perror("execlp pythonscript");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//	function to initialize the pipes and data size written into the pipes
int	init_pipe_data(t_win_data *window, int *i)
{
	window->thread_data[*i].pipe_fd[0] = -1;
	window->thread_data[*i].pipe_fd[1] = -1;
	if (pipe(window->thread_data[*i].pipe_fd) == -1)
		return (free_threads(window, "Pipe error"));
	ft_printf("\033[0;34mPipe %d:\033[0m read fd = %d, write fd = %d\n",
		*i, window->thread_data[*i].pipe_fd[0],
		window->thread_data[*i].pipe_fd[1]);
	if (*i == 0)
		window->thread_data[*i].write_size = 3 * sizeof(int);
	else if (*i == 1)
		window->thread_data[*i].write_size = 2 * sizeof(int);
	else if (*i == 2)
		window->thread_data[*i].write_size = 2 * sizeof(int);
	else if (*i == 3)
		window->thread_data[*i].write_size = sizeof(int);
	(*i)++;
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
		return (free_threads(window, "malloc thread data"));
	ft_printf("\n\033[0;35mCreating pipes...\033[0m\n");
	i = 0;
	while (i < 4)
		if (init_pipe_data(window, &i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (redirect_pipe_execute_python_script(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < 4)
		if (close(window->thread_data[i++].pipe_fd[0]) == -1)
			return (free_threads(window, "close read fd"));
	return (EXIT_SUCCESS);
}
