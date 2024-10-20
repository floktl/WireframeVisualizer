/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:14:58 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/18 21:26:15 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	thread loop to write the right data into each thread (runs simultanly)
void	*pipe_writer(void *arg)
{
	t_pipe_thread_data	*data;
	static struct timeval last_write_time = {0};
	struct timeval		current_time;
	long				elapsed_time;

	data = (t_pipe_thread_data *)arg;
	if (data->pipe_index < 0 || data->pipe_index >= 4)
		return (fprintf(stderr, "Invalid pipe %d\n", data->pipe_index), NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000
			+ (current_time.tv_usec - last_write_time.tv_usec);
		if (elapsed_time >= WRITE_INTERVAL)
		{
			if (write_into_pipes(data) == -1)
				return (NULL);
			last_write_time = current_time;
		}
		else
			usleep(100);
	}
	return (NULL);
}

//	function to create detached threads for the data visualization
int	pipe_data_multithreaded(t_win_data *window)
{
	int					i;

	pthread_mutex_init(&window->map_sz.data_mutex, NULL);
	window->map_sz.running = 1;
	if (!window->thread_data)
	{
		perror("Failed to allocate memory for thread data");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < 4)
	{
		pthread_mutex_init(&window->thread_data[i].data_mutex, NULL);
		window->thread_data[i].pipe_index = i;
		if (pthread_create(&window->threads[i], NULL,
				pipe_writer, &window->thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			free(window->thread_data);
			return (EXIT_FAILURE);
		}
		pthread_detach(window->threads[i++]);
	}
	return (EXIT_SUCCESS);
}

//	function to stop all threads from running
void	cleanup_threads(t_map_data *map_data)
{
	pthread_mutex_lock(&map_data->data_mutex);
	map_data->running = 0;
	pthread_mutex_unlock(&map_data->data_mutex);
}
