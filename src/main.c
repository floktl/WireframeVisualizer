/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:51:31 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/16 19:11:20 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// -----------------------------------------------------------------------------

void *pipe_writer(void *arg)
{
	t_pipe_thread_data *data = (t_pipe_thread_data *)arg;
	struct timeval last_write_time = {0};
	struct timeval current_time;
	long elapsed_time;

	if (data->pipe_index < 0 || data->pipe_index >= 4)
	{
		fprintf(stderr, "Invalid pipe index: %d\n", data->pipe_index);
		return (NULL);
	}
	//int z = 0;
	int rot_x;
	int rot_y;
	int rot_z;
	int xm;
	int ym;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000
					+ (current_time.tv_usec - last_write_time.tv_usec);

		if (elapsed_time >= WRITE_INTERVAL)
		{
			if (data->pipe_fd[1] <= 0)
			{
				fprintf(stderr, "Invalid pipe file descriptor: %d\n", data->pipe_fd[1]);
				return(NULL);
			}
			if (data->pipe_fd[1] > 0)
			{
				pthread_mutex_lock(&data->data_mutex);
				rot_x = data->rot_x;
				rot_y = data->rot_y;
				rot_z = data->rot_z;
				xm = data->xposmw;
				ym = data->yposmw;
				pthread_mutex_unlock(&data->data_mutex);
				//printf("Pipe writer thread %d: xposmw=%d, yposmw=%d, rot_x=%d, rot_y=%d, rot_z=%d\n",
				// 	data->pipe_index, xm, ym, rot_x, rot_y, rot_z);
				if (data->pipe_index == 0)
				{
					if (write(data->pipe_fd[1], &rot_x, sizeof(int)) == -1 ||
						write(data->pipe_fd[1], &rot_y, sizeof(int)) == -1 ||
						write(data->pipe_fd[1], &rot_z, sizeof(int)) == -1)
					{
						perror("write error (rotation)");
						close(data->pipe_fd[1]);
						data->pipe_fd[1] = -1;
					}
				}
				else if (data->pipe_index == 1)
				{
					if (write(data->pipe_fd[1], &xm, sizeof(int)) == -1 ||
						write(data->pipe_fd[1], &ym, sizeof(int)) == -1)
					{
						perror("write error (position)");
						close(data->pipe_fd[1]);
						data->pipe_fd[1] = -1;
					}
				}
				last_write_time = current_time;
			}
		}
		usleep(10000);
	}
	return (NULL);
}



int pipe_data_multithreaded(t_window *window)
{
	int					i;

	pthread_mutex_init(&window->map_sz.data_mutex, NULL);
	window->map_sz.running = 1;
	if (!window->thread_data)
	{
		perror("Failed to allocate memory for thread data");
		return (EXIT_FAILURE);
	}
	for (i = 0; i < 4; i++)
	{
		pthread_mutex_init(&window->thread_data[i].data_mutex, NULL);
		window->thread_data[i].pipe_index = i;
		if (pthread_create(&window->threads[i], NULL, pipe_writer, &window->thread_data[i]) != 0)
		{
			perror("Failed to create thread");
			free(window->thread_data);
			return (EXIT_FAILURE);
		}
		pthread_detach(window->threads[i]);
	}
	return (EXIT_SUCCESS);
}

void	cleanup_threads(t_sz *map_data)
{
	pthread_mutex_lock(&map_data->data_mutex);
	map_data->running = 0;
	pthread_mutex_unlock(&map_data->data_mutex);
}


int	main(int argc, char *argv[])
{
	t_window	window;
	//int			i;

	if (argc != 2)
		return (ft_printf("usage: ./fdf <map>.fdf\n"), EXIT_FAILURE);
	if (check_defines() == EXIT_FAILURE
		|| initialize_window_from_args(&window, argv) == EXIT_FAILURE
		|| set_coord(&window) == EXIT_FAILURE
		|| create_pipe(&window) == EXIT_FAILURE
		|| pipe_data_multithreaded(&window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	free_map(window.map);
	if (initialize_mlx_image(&window) == EXIT_FAILURE)
		return (ft_shutdown_error(window.mlx));
	mlx_resize_hook(window.mlx, ft_resize, &window);
	mlx_scroll_hook(window.mlx, ft_scroll, &window);
	mlx_loop_hook(window.mlx, ft_render, &window);
	mlx_loop(window.mlx);
	cleanup_threads(&window.map_sz);
	//i = 0;
	// while (i < 4)
	// 	close(window.thread_data[i].pipe_fd[1]);
	free_map_coordinates(&window.coord);
	free_manual(&window.manual);
	pthread_mutex_destroy(&window.map_sz.data_mutex);
	mlx_terminate(window.mlx);
	return (EXIT_SUCCESS);
}
