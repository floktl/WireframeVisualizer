/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_additional_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 07:33:54 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 16:22:36 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//	this function resets the map settings to the default settings
int	reset_map(t_window *window)
{
	t_coord		*coord;
	static int	key_pressed = OFF;

	if (mlx_is_key_down(window->mlx, MLX_KEY_T) && key_pressed == OFF)
	{
		ft_printf("\033[0;35mReset map...\033[0m\n");
		clear_image(window, DEFAULT_WINDOW_COLOR);
		set_map_to_middle(window);
		reset_map_size(window);
		coord = window->coord;
		while (coord != NULL)
		{
			update_mapsize(&window->map_sz, coord);
			rotation_calc(window, coord);
			coord = coord->next;
		}
		return (key_pressed = ON, CHANGE);
	}
	else if (!mlx_is_key_down(window->mlx, MLX_KEY_T))
		key_pressed = OFF;
	return (NO_CHANGE);
}

//	this function enables the debug mode and resets the map with the key T
int	debug_mode_map(t_window *window)
{
	static int	key_pressed = OFF;

	if (mlx_is_key_down(window->mlx, MLX_KEY_D) && key_pressed == OFF)
	{
		if (window->debug_mode == OFF)
			window->debug_mode = ON;
		else if (window->debug_mode == ON)
			window->debug_mode = OFF;
		if (window->debug_mode == ON)
		{
			mlx_set_window_title(window->mlx, "fdf --DEBUG MODE ENABLED--");
			ft_printf("\033[0;33m\n\nDEBUG MODE ENABLED...\033[0m\n");
			ft_printf(
				"\033[0;35mAdjust the debug points as you like...\033[0m\n");
		}
		else
			mlx_set_window_title(window->mlx, "fdf");
		key_pressed = ON;
		return (CHANGE);
	}
	else if (!mlx_is_key_down(window->mlx, MLX_KEY_D))
		key_pressed = OFF;
	return (NO_CHANGE);
}

//	function enables the manual
int	information(t_window *window)
{
	static int	key_pressed = OFF;
	static int	manual_status = ON;

	if (mlx_is_key_down(window->mlx, MLX_KEY_I) && key_pressed == OFF)
	{
		if (manual_status == OFF)
		{
			remove_manual_from_window(window);
			manual_status = ON;
		}
		else if (manual_status == ON)
		{
			manual_status = OFF;
			print_manual(window);
		}
		key_pressed = ON;
		return (CHANGE);
	}
	else if (!mlx_is_key_down(window->mlx, MLX_KEY_I))
		key_pressed = OFF;
	return (NO_CHANGE);
}
