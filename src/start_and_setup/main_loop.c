/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:33 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/19 07:14:09 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//
//-------------- main loop for the programm, it runs constantly----------------
//

//	function to update the thread struct with the current data changes
void	update_thread_struct(t_win_data *window)
{
	static struct timeval	last_write_time = {0};
	struct timeval	current_time;
	long			elapsed_time;
	int				i;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - last_write_time.tv_sec) * 1000000
		+ (current_time.tv_usec - last_write_time.tv_usec);
	if (elapsed_time >= 10000)
	{
		i = 0;
		while (i < 4)
		{
			if (i == 0)
			{
				pthread_mutex_lock(&window->thread_data[i].data_mutex);
				window->thread_data[i].value1 = window->map_sz.xm_rot_deg;
				window->thread_data[i].value2 = window->map_sz.ym_rot_deg;
				window->thread_data[i].value3 = window->map_sz.zm_rot_deg;
				pthread_mutex_unlock(&window->thread_data[i++].data_mutex);
			}
			else if (i == 1)
			{
				pthread_mutex_lock(&window->thread_data[i].data_mutex);
				window->thread_data[i].value1 = window->map_sz.xposmw;
				window->thread_data[i].value2 = window->map_sz.yposmw;
				pthread_mutex_unlock(&window->thread_data[i++].data_mutex);
			}
			else if (i == 2)
			{
				pthread_mutex_lock(&window->thread_data[i].data_mutex);
				window->thread_data[i].value1 = window->mouse_posx;
				window->thread_data[i].value2 = window->mouse_posy;
				pthread_mutex_unlock(&window->thread_data[i++].data_mutex);
			}
			else if (i == 3)
			{
				pthread_mutex_lock(&window->thread_data[i].data_mutex);
				window->thread_data[i].value1 = window->map_sz.map_area;
				pthread_mutex_unlock(&window->thread_data[i++].data_mutex);
			}
		}
		last_write_time = current_time;
	}
}

// fills the window with the map rendered in 3D functionality
void	ft_render(void *param)
{
	t_win_data	*window;
	t_coord		*current;
	int			x_offset;
	int			y_offset;

	x_offset = 0;
	y_offset = 0;
	window = (t_win_data *)param;
	(void)window;
	mlx_get_mouse_pos(window->mlx, &window->mouse_posx, &window->mouse_posy);
	check_margin_border(window);
	clear_image(window, DEFAULT_WINDOW_COLOR);
	if (ft_hook_key(window, &x_offset, &y_offset) == CHANGE)
		update_coord(window, x_offset, y_offset);
	print_debug_point_1(window);
	print_debug_point_2(window);
	current = window->coord;
	while (current != NULL && current->next != NULL)
	{
		if (current->pos_ym == current->next->pos_ym)
			connect_points(window, current, current->next);
		connect_points(window, current, current->next_y);
		current = current->next;
	}
	update_thread_struct(window);
}

//	hook functions for keyboard user input:
//	arrow keys: moving map in x and y direction
//	P: Zoom in M: Zoom out
//	R + arrow keys: rotate map in x and y direction
//	D: Debug mode with terminal value view option and map center visualization
int	ft_hook_key(t_win_data *window, int *x_offset, int *y_offset)
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
