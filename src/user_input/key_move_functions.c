/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_move_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:06:21 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/20 07:35:55 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//-------- these fucntions handles the calclualtion for key user input ---------
//

//	this function calculates the shift of the map with the arrow keys
int	shift_map(t_window *window, int *x_set, int *y_set)
{
	int			shift_speed;

	shift_speed = SHIFT_DEFAULT
		* (window->height + window->width) / (HEIGHT + WIDTH);
	if (mlx_is_key_down(window->mlx, MLX_KEY_UP)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_DOWN))
		*y_set = range_check(window, 0, -shift_speed, Z);
	if (mlx_is_key_down(window->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_UP))
		*y_set = range_check(window, 0, shift_speed, Z);
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		*x_set = range_check(window, -shift_speed, 0, Z);
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		*x_set = range_check(window, shift_speed, 0, Z);
	return (CHANGE);
}

//	this function nandles the zoom when the user presses P or M
double	zoom_map(t_window *window)
{
	if (window->zoom != ZOOM_DEFAULT)
		return (NO_CHANGE);
	if ((mlx_is_key_down(window->mlx, MLX_KEY_P)
			&& !mlx_is_key_down(window->mlx, MLX_KEY_M))
		&& window->zoom == ZOOM_DEFAULT)
		if (window->map_sz.map_area * ZOOM_P < window->max_zoom_size)
			window->zoom = ZOOM_P;
	if (mlx_is_key_down(window->mlx, MLX_KEY_M)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_P)
		&& window->zoom == ZOOM_DEFAULT)
		if (window->map_sz.map_area * ZOOM_M > window->min_zoom_size)
			window->zoom = ZOOM_M;
	return (CHANGE);
}

//	function to rotate
double	rotate_map(t_window *window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_R)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_L))
		window->map_sz.xm_rot_deg += ROTATION_SPEED;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_L)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_R))
		window->map_sz.xm_rot_deg += -ROTATION_SPEED;
	if (mlx_is_key_down(window->mlx, MLX_KEY_N)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_J))
		window->map_sz.ym_rot_deg += ROTATION_SPEED;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_J)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_N))
		window->map_sz.ym_rot_deg += -ROTATION_SPEED;
	if (mlx_is_key_down(window->mlx, MLX_KEY_G)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_H))
		window->map_sz.zm_rot_deg += ROTATION_SPEED;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_H)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_G))
		window->map_sz.zm_rot_deg += -ROTATION_SPEED;
	degree(&window->map_sz.xm_rot_deg);
	degree(&window->map_sz.ym_rot_deg);
	degree(&window->map_sz.zm_rot_deg);
	return (NO_CHANGE);
}

// function to change the z axis of the map
int	change_height_map(t_window *window)
{
	if (mlx_is_key_down(window->mlx, MLX_KEY_Z))
		window->map_sz.height_change += HEIGHT_FAKTOR;
	else if (mlx_is_key_down(window->mlx, MLX_KEY_A))
		window->map_sz.height_change -= HEIGHT_FAKTOR;
	return (NO_CHANGE);
}
