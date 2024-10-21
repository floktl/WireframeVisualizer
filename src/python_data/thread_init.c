/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:14:58 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/21 07:56:27 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	function to create detached threads for the data visualization
int	pipe_data_multithreaded(t_win_data *window)
{
	int	i;

	if (!window->thread_data)
		return (free_threads(window, "Failed to allocate thread data memory"));
	i = 0;
	while (i < 4)
	{
		window->thread_data[i].is_mutex_initialized = 0;
		if (pthread_mutex_init(&window->thread_data[i].data_mutex, NULL) != 0)
			return (free_threads(window, "Failed to init thread_data mutex"));
		window->thread_data[i].is_mutex_initialized = 1;
		window->thread_data[i].pipe_index = i;
		if (pthread_create(&window->threads[i], NULL, pipe_writer,
				&window->thread_data[i]) != 0)
			return (free_threads(window, "Failed to create thread"));
		if (pthread_detach(window->threads[i]) != 0)
			return (free_threads(window, "Failed to detach thread"));
		i++;
	}
	return (EXIT_SUCCESS);
}


