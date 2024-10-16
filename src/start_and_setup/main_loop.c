/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:33 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/16 13:16:00 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//
//-------------- main loop for the programm, it runs constantly----------------
//

// fills the window with the map rendered in 3D functionality
void ft_render(void *param)
{
	(void)param;
	t_window *window;
	t_coord *current;
	int x_offset;
	int y_offset;

	x_offset = 0;
	y_offset = 0;
	window = (t_window *)param;
	(void)window;
	mlx_get_mouse_pos(window->mlx, &window->mouse_posx, &window->mouse_posy);
	check_margin_border(window);
	clear_image(window, DEFAULT_WINDOW_COLOR);
	//pthread_mutex_lock(&window->map_sz.data_mutex);
	if (ft_hook_key(window, &x_offset, &y_offset) == CHANGE)
	{
		update_coord(window, x_offset, y_offset);
	}
	print_debug_point_1(window);
	print_debug_point_2(window);
	//pthread_mutex_unlock(&window->map_sz.data_mutex);
	current = window->coord;
	while (current != NULL && current->next != NULL)
	{
		if (current->pos_ym == current->next->pos_ym)
			connect_points(window, current, current->next);
		connect_points(window, current, current->next_y);
		current = current->next;
	}
	
}

//	hook functions for keyboard user input:
//	arrow keys: moving map in x and y direction
//	P: Zoom in M: Zoom out
//	R + arrow keys: rotate map in x and y direction
//	D: Debug mode with terminal value view option and map center visualization
int	ft_hook_key(t_window *window, int *x_offset, int *y_offset)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(window->mlx);
	debug_mode_map(window);
	change_height_map(window);
	shift_map(window, x_offset, y_offset);
	mouse_shift(window, x_offset, y_offset);
	mouse_rotation(window);
	zoom_map(window);
	rotate_map(window);
	information(window);
	if (window->zoom == ZOOM_DEFAULT
		&& *x_offset == NO_CHANGE
		&& *y_offset == NO_CHANGE
		&& check_change_in_rotation(window) == NO_CHANGE
		&& check_change_height(window) == NO_CHANGE
		&& reset_map(window) == NO_CHANGE)
		return (NO_CHANGE);
	return (CHANGE);
}

// sending notification via pushover app
// static int push_block = 0;
// static int previous_rot = 0;
// if (previous_rot != window->map_sz.xm_rot_deg
// 	&& mlx_is_key_down(window->mlx, MLX_KEY_E))
// 	push_block = 0;
// if (mlx_is_key_down(window->mlx, MLX_KEY_Q) && push_block == 0
// 	&& previous_rot != window->map_sz.xm_rot_deg)
// {
// 	push_block = 1;
// 	previous_rot = window->map_sz.xm_rot_deg;
// 	char command[256];
// 	snprintf(command, sizeof(command),
// 		"python3 push.py \"rotation degree: %d\"",
// 			window->map_sz.xm_rot_deg);
// 	system(command);
// }
