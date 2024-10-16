/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:04:14 by flo               #+#    #+#             */
/*   Updated: 2024/10/16 06:10:29 by flo              ###   ########.fr       */
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
	// Create 4 unnamed pipes
	while (i < 4)
	{
		if (pipe(window->map_sz.pipe_fd[i]) == -1)
			return (perror("pipe"), EXIT_FAILURE);
		ft_printf("Pipe %d created: read fd = %d, write fd = %d\n",
				i, window->map_sz.pipe_fd[i][0], window->map_sz.pipe_fd[i][1]);
		i++;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0) // Child process
	{
		i = 0;
		// Close the write ends of all pipes
		while (i < 4)
		{
			close(window->map_sz.pipe_fd[i][1]); // Close write end for each pipe
			dup2(window->map_sz.pipe_fd[i][0], i + 3); // Redirect the read ends to fd 3, 4, 5, 6
			i++;
		}
		// Execute the Python script
		execlp("python3", "python3", "src/python_data/visualize_struct.py", NULL);
		perror("execlp"); // Only reached if execlp fails
		exit(EXIT_FAILURE);
	}

	// Close the read ends in the parent process
	i = 0;
	while (i < 4)
	{
		close(window->map_sz.pipe_fd[i][0]);
		i++;
	}

	return (EXIT_SUCCESS);
}

