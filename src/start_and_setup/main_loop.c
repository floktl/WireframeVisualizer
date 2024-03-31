/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 09:45:33 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/24 14:14:55 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//-------------- main loop for the programm, it runs constantly----------------
//

//fills the window with the map rendered in 3d functionality
void	ft_render(void *param)
{
	t_window	*window;
	t_coord		*current;
	int			x_offset;
	int			y_offset;

	x_offset = 0;
	y_offset = 0;
	window = (t_window *)param;
	mlx_get_mouse_pos(window->mlx, &window->mouse_posx, &window->mouse_posy);
	check_margin_border(window);
	clear_image(window, DEFAULT_WINDOW_COLOR);
	if (ft_hook_key(window, &x_offset, &y_offset) == CHANGE)
	{
		update_coord(window, x_offset, y_offset);
	}
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
