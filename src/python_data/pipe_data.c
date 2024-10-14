/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/14 17:09:10 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to create the pipe and start the python script for visual data
int create_pipe(t_window *window)
{
	pid_t pid;

	if (pipe(window->pipe_fd) == -1)
		return (perror("pipe"), EXIT_FAILURE);
	ft_printf("Pipe created: read fd = %d, write fd = %d\n",
		window->pipe_fd[0], window->pipe_fd[1]);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(window->pipe_fd[1]);
		dup2(window->pipe_fd[0], STDIN_FILENO);
		close(window->pipe_fd[0]);
		execlp("python3", "python3", "src/python_data/visualize_struct.py", NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	close(window->pipe_fd[0]);
	return (EXIT_SUCCESS);
}

//	function to write the struct data to the pipe for the python script visul.
void	pipe_data(t_window *window)
{
	static struct timeval last_write_time;
	struct timeval current_time;
	long elapsed_time;
	int py_pipe;

	py_pipe = window->pipe_fd[1];
	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000 +
				(current_time.tv_usec - last_write_time.tv_usec);
	if (elapsed_time >= WRITE_INTERVAL)
	{
		if (py_pipe > 0)
		{
			if (write(py_pipe, &window->map_sz.xposmw, sizeof(int))
				== -1)
				perror("write error");
			if (write(py_pipe, &window->map_sz.yposmw, sizeof(int))
				== -1)
				perror("write error");
			last_write_time = current_time;
		}
		else
			printf("Pipe write fd is invalid: %d\n", py_pipe);
	}
}
