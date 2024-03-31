/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:58:34 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/18 18:49:44 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//------ these fucntions handles the calclualtion for mouse user input --------
//

//	checks if the mouse button clicked and the pointer in the image
int	check_mouse_clicked(t_window *window, int x, int y, enum mouse_key key)
{
	if (mlx_is_mouse_down(window->mlx, key))
	{
		if (x > 0 && x < window->width && y > 0 && y < window->height)
		{
			return (CHANGE);
		}
	}
	return (NO_CHANGE);
}

//	calculates the shift of the map, with the left button clicked
int	mouse_shift(t_window *window, int *x_set, int *y_set)
{
	static int	previous_x = 0;
	static int	previous_y = 0;
	int			x;
	int			y;

	mlx_get_mouse_pos(window->mlx, &x, &y);
	if (check_mouse_clicked(window, x, y, MLX_MOUSE_BUTTON_LEFT) == 1)
	{
		x -= previous_x;
		y -= previous_y;
		x = range_check(window, x, 0, Z);
		y = range_check(window, 0, y, Z);
	}
	else
	{
		x = 0;
		y = 0;
	}
	previous_x = window->mouse_posx;
	previous_y = window->mouse_posy;
	*x_set += x;
	*y_set += y;
	return (NO_CHANGE);
}

//	calculates the rotation of the map, with the right button clicked
int	mouse_rotation(t_window *window)
{
	static int	previous_x = 0;
	static int	previous_y = 0;
	int			x;
	int			y;

	mlx_get_mouse_pos(window->mlx, &x, &y);
	if (check_mouse_clicked(window, x, y, MLX_MOUSE_BUTTON_RIGHT) == 1)
	{
		x -= previous_x;
		y -= previous_y;
	}
	else
	{
		x = 0;
		y = 0;
	}
	previous_x = window->mouse_posx;
	previous_y = window->mouse_posy;
	window->map_sz.ym_rot_deg -= x * ROTATION_FACTOR;
	window->map_sz.xm_rot_deg += y * ROTATION_FACTOR;
	return (NO_CHANGE);
}
