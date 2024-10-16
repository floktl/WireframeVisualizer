/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:51:31 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/16 06:31:08 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// -----------------------------------------------------------------------------

// Declare a mutex

void *pipe_writer(void *arg)
{
	t_pipe_thread_data *data = (t_pipe_thread_data *)arg;
	int pipe_index = data->pipe_index;
	t_sz *map_data = data->map_data;
	struct timeval last_write_time = {0};
	struct timeval current_time;
	long elapsed_time;

	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000 +
					(current_time.tv_usec - last_write_time.tv_usec);

		if (elapsed_time >= WRITE_INTERVAL)
		{

			if (map_data->pipe_fd[pipe_index][1] > 0)
			{
				pthread_mutex_lock(&map_data->data_mutex);
				if (pipe_index == 0)
				{
					// if (write(map_data->pipe_fd[pipe_index][1], &map_data->xm_rot_deg, sizeof(int)) == -1 ||
					// 	write(map_data->pipe_fd[pipe_index][1], &map_data->ym_rot_deg, sizeof(int)) == -1 ||
					// 	write(map_data->pipe_fd[pipe_index][1], &map_data->zm_rot_deg, sizeof(int)) == -1)
					// {
					// 	perror("write error (rotation)");
					// 	close(map_data->pipe_fd[pipe_index][1]);
					// 	map_data->pipe_fd[pipe_index][1] = -1;
					// }
				}
				else if (pipe_index > 0)
				{
					// if (write(map_data->pipe_fd[pipe_index][1], &map_data->xposmw, sizeof(int)) == -1 ||
					// 	write(map_data->pipe_fd[pipe_index][1], &map_data->yposmw, sizeof(int)) == -1)
					// {
					// 	perror("write error (position)");
					// 	close(map_data->pipe_fd[pipe_index][1]);
					// 	map_data->pipe_fd[pipe_index][1] = -1;
					// }
				}
				pthread_mutex_unlock(&map_data->data_mutex);
				last_write_time = current_time;
			}
			else
			{
				printf("Pipe write fd is invalid for pipe %d: %d\n", pipe_index, map_data->pipe_fd[pipe_index][1]);
			}

			pthread_mutex_unlock(&map_data->data_mutex);
		}

		usleep(1000);
	}
	return (NULL);
}


int pipe_data_multithreaded(t_sz *map_data)
{
	pthread_t threads[4];
	t_pipe_thread_data thread_data[4];
	int i;

	for (i = 0; i < 4; i++)
	{
		thread_data[i].map_data = map_data;
		thread_data[i].pipe_index = i;
		if (pthread_create(&threads[i], NULL, pipe_writer, &thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
	t_window window; // Window struct

	// Step 1: Argument validation
	if (argc != 2)
		return (ft_printf("usage: ./fdf <map>.fdf\n"), EXIT_FAILURE);

	// Step 2: Various initialization steps
	if (check_defines() == EXIT_FAILURE
		|| initialize_window_from_args(&window, argv) == EXIT_FAILURE
		|| set_coord(&window) == EXIT_FAILURE
		|| create_pipe(&window) == EXIT_FAILURE) // Pipe creation
		return (EXIT_FAILURE);

	// Step 3: Free map, if necessary
	free_map(window.map);
	pthread_mutex_init(&window.map_sz.data_mutex, NULL);
	// Step 4: Initialize the MLX image
	if (initialize_mlx_image(&window) == EXIT_FAILURE)
		return (ft_shutdown_error(window.mlx));

	// Step 5: Start the multithreaded pipe data function
	if (pipe_data_multithreaded(&window.map_sz) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// Step 6: Set hooks for resizing, scrolling, rendering, etc.
	//mlx_resize_hook(window.mlx, ft_resize, &window);
	//mlx_scroll_hook(window.mlx, ft_scroll, &window);
	mlx_loop_hook(window.mlx, ft_render, &window);

	// Step 7: Start the MLX loop
	//mlx_loop(window.mlx);

	// Step 8: Close pipe file descriptors (write end)
	for (int i = 0; i < 4; i++)
	{
		close(window.map_sz.pipe_fd[i][1]); // Close write end of each pipe
	}
	// Step 9: Wait for child process (if you forked it for the Python script)
	//wait(NULL);

	// Step 10: Free dynamically allocated resources
	free_map_coordinates(&window.coord);
	free_manual(&window.manual);
	pthread_mutex_destroy(&window.map_sz.data_mutex);
	mlx_terminate(window.mlx); // Terminate MLX

	return (EXIT_SUCCESS);
}

