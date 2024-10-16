/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:51:31 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/16 10:04:35 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// -----------------------------------------------------------------------------

void	*pipe_writer(void *arg)
{
	t_pipe_thread_data	*data;
	int					pipe_index;
	t_sz				*map_data;
	struct timeval		last_write_time = {0};
	struct timeval		current_time;
	long				elapsed_time;

	data = (t_pipe_thread_data *)arg;
	pipe_index = data->pipe_index;
	map_data = data->map_data;
	if (pipe_index < 0 || pipe_index >= 4)
	{
		fprintf(stderr, "Invalid pipe index: %d\n", pipe_index);
		return (NULL);
	}
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000
			+ (current_time.tv_usec - last_write_time.tv_usec);
		if (elapsed_time >= WRITE_INTERVAL)
		{
			if (map_data->pipe_fd[pipe_index][1] > 0)
			{
				if (pipe_index == 0)
				{
					//pthread_mutex_lock(&map_data->data_mutex);
					if (write(map_data->pipe_fd[pipe_index][1],
						&map_data->xm_rot_deg, sizeof(int)) == -1 ||
						write(map_data->pipe_fd[pipe_index][1],
							&map_data->ym_rot_deg, sizeof(int)) == -1 ||
						write(map_data->pipe_fd[pipe_index][1],
							&map_data->zm_rot_deg, sizeof(int)) == -1)
					{
						//pthread_mutex_unlock(&map_data->data_mutex);
						perror("write error (rotation)");
						close(map_data->pipe_fd[pipe_index][1]);
						map_data->pipe_fd[pipe_index][1] = -1;
					}
					//pthread_mutex_unlock(&map_data->data_mutex);
				}
				else if (pipe_index > 0)
				{
					//pthread_mutex_lock(&map_data->data_mutex);
					if (write(map_data->pipe_fd[pipe_index][1],
						&map_data->xposmw, sizeof(int)) == -1 ||
						write(map_data->pipe_fd[pipe_index][1],
							&map_data->yposmw, sizeof(int)) == -1)
					{
						//pthread_mutex_unlock(&map_data->data_mutex);
						perror("write error (position)");
						close(map_data->pipe_fd[pipe_index][1]);
						map_data->pipe_fd[pipe_index][1] = -1;
					}
					//pthread_mutex_unlock(&map_data->data_mutex);
				}
				last_write_time = current_time;
			}
			else
			{
				printf("Pipe write fd is invalid for pipe %d: %d\n",
					pipe_index, map_data->pipe_fd[pipe_index][1]);
			}
		}
		usleep(50);
	}
	return (NULL);
}



int pipe_data_multithreaded(t_sz *map_data)
{
	pthread_t			threads[4];
	t_pipe_thread_data	*thread_data;
	int					i;

	pthread_mutex_init(&map_data->data_mutex, NULL);
	map_data->running = 1;
	thread_data = malloc(sizeof(t_pipe_thread_data) * 4);
	if (!thread_data)
	{
		perror("Failed to allocate memory for thread data");
		return (EXIT_FAILURE);
	}
	for (i = 0; i < 4; i++)
	{
		thread_data[i].map_data = map_data;
		thread_data[i].pipe_index = i;
		if (pthread_create(&threads[i], NULL, pipe_writer, &thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			free(thread_data);
			return (EXIT_FAILURE);
		}
		pthread_detach(threads[i]);
	}
	map_data->thread_data = thread_data;
	return (EXIT_SUCCESS);
}

void	cleanup_threads(t_sz *map_data)
{
	pthread_mutex_lock(&map_data->data_mutex);
	map_data->running = 0;
	pthread_mutex_unlock(&map_data->data_mutex);
}


int main(int argc, char *argv[])
{
	t_window window;
	int i;

	if (argc != 2)
		return (ft_printf("usage: ./fdf <map>.fdf\n"), EXIT_FAILURE);
	if (check_defines() == EXIT_FAILURE
		|| initialize_window_from_args(&window, argv) == EXIT_FAILURE
		|| set_coord(&window) == EXIT_FAILURE
		|| create_pipe(&window) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	free_map(window.map);

	if (initialize_mlx_image(&window) == EXIT_FAILURE
		|| pipe_data_multithreaded(&window.map_sz) == EXIT_FAILURE)
		return (ft_shutdown_error(window.mlx));

	mlx_resize_hook(window.mlx, ft_resize, &window);
	mlx_scroll_hook(window.mlx, ft_scroll, &window);
	mlx_loop_hook(window.mlx, ft_render, &window);

	// Main loop can perform its own tasks here
	// For example, running until an exit condition or user input
	mlx_loop(window.mlx);
	// Clean up threads
	// Setting the running flag to 0 will signal threads to stop
	cleanup_threads(&window.map_sz); // Call this function to stop threads

	// Close pipes and free resources
	for (i = 0; i < 4; i++)
		close(window.map_sz.pipe_fd[i][1]);

	free_map_coordinates(&window.coord);
	free_manual(&window.manual);
	pthread_mutex_destroy(&window.map_sz.data_mutex);
	mlx_terminate(window.mlx);

	return (EXIT_SUCCESS);
}
