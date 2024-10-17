/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/16 18:25:57 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// function to create the pipes and start the Python script for visual data
// function to create the pipes and start the Python script for visual data
int create_pipe(t_window *window)
{
	int i;
	pid_t pid;

	i = 0;
	window->threads = malloc(sizeof(pthread_t) * 4);
	if (!window->threads)
	{
		perror("malloc threads");
		return (EXIT_FAILURE);
	}
	window->thread_data = malloc(sizeof(t_pipe_thread_data) * 4);
	if (!window->thread_data)
	{
		perror("malloc thread_data");
		return (EXIT_FAILURE);
	}
	// Create 4 unnamed pipes
	while (i < 4)
	{
		if (pipe(window->thread_data[i].pipe_fd) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		// ft_printf("Pipe %d created: read fd = %d, write fd = %d\n",
		// 		i, window->thread_data[i].pipe_fd[0],
		// 		window->thread_data[i].pipe_fd[1]);
		i++;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		i = 0;
		while (i < 4)
		{
			close(window->thread_data[i].pipe_fd[1]);
			dup2(window->thread_data[i].pipe_fd[0], i + 3);
			//printf("end of Pipe %i redirected to fd %i\n", i, i + 3);
			i++;
		}
		//printf("Execute the Python script\n");
		execlp("python3", "python3", "src/python_data/visualize_struct.py", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}

	// Close the read ends in the parent process
	i = 0;
	while (i < 4)
	{
		close(window->thread_data[i].pipe_fd[0]);
		i++;
	}
	return (EXIT_SUCCESS);
}

