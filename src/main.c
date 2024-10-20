/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:51:31 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/20 12:01:09 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// -----------------------------------------------------------------------------

int	main(int argc, char *argv[])
{
	t_win_data	data;

	if (argc != 2)
		return (ft_printf("usage: ./fdf <map>.fdf\n"), EXIT_FAILURE);
	if (check_defines() == EXIT_FAILURE
		|| initialize_window_from_args(&data, argv) == EXIT_FAILURE
		|| set_coord(&data) == EXIT_FAILURE
		|| create_pipe(&data) == EXIT_FAILURE
		|| pipe_data_multithreaded(&data) == EXIT_FAILURE)
		return (free_map(data.map), EXIT_FAILURE);
	free_map(data.map);
	if (initialize_mlx_image(&data) == EXIT_FAILURE)
		return (kill_python_process(&data.python_pid),
			ft_shutdown_error(data.mlx));
	mlx_resize_hook(data.mlx, ft_resize, &data);
	mlx_scroll_hook(data.mlx, ft_scroll, &data);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_loop(data.mlx);
	free_map_coordinates(&data.coord);
	free_manual(&data.manual);
	pthread_mutex_destroy(&data.map_sz.data_mutex);
	mlx_terminate(data.mlx);
	kill_python_process(&data.python_pid);
	return (EXIT_SUCCESS);
}
