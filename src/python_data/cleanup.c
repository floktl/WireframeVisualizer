/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:46:06 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/21 08:18:34 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to free the allocated memory for threads and thread data
int	free_threads(t_win_data *window, const char *err_str)
{
	int	i;

	if (window->threads)
	{
		i = 0;
		while (i < 4)
			if (window->threads[i++])
				pthread_cancel(window->threads[i - 1]);
		free(window->threads);
		window->threads = NULL;
	}
	if (window->thread_data)
	{
		i = 0;
		while (i < 4)
		{
			if (window->thread_data[i].pipe_fd[0] != -1)
				if (close(window->thread_data[i].pipe_fd[0]) == -1)
					perror("Failed to close read fd");
			if (window->thread_data[i].pipe_fd[1] != -1)
				if (close(window->thread_data[i].pipe_fd[1]) == -1)
					perror("Failed to close write fd");
			if (window->thread_data[i++].is_mutex_initialized)
				pthread_mutex_destroy(&window->thread_data[i - 1].data_mutex);
		}
		free(window->thread_data);
		window->thread_data = NULL;
	}
	if (err_str != NULL)
		perror(err_str);
	return (EXIT_FAILURE);
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
