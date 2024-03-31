/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigning_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:33:01 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 10:44:20 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//---------------- functions to assign the data for the structs ---------------
//

//----------------------------- window struct ----------------------------------

//	sets the default settings for the window
int	set_default_window_data(t_window *window)
{
	if (!window)
		return (perror("Error setting default window data"), EXIT_FAILURE);
	window->start_size = (WIDTH / (window->map_sz.xm_size + 2));
	window->cent_xw = WIDTH / 2;
	window->cent_yw = HEIGHT / 2;
	window->map_sz.xm_offset = OFFSET_DEFAULT;
	window->map_sz.ym_offset = OFFSET_DEFAULT;
	window->map_sz.zm_offset = OFFSET_DEFAULT;
	window->map_sz.height_change = HEIGHT_DEFAULT;
	window->debug_mode = OFF;
	window->width = WIDTH;
	window->height = HEIGHT;
	window->zoom = ZOOM_DEFAULT;
	window->max_zoom_size = WIDTH * HEIGHT * MAX_MAP_SIZE;
	window->min_zoom_size = (WIDTH * HEIGHT) / MIN_MAP_SIZE;
	return (EXIT_SUCCESS);
}

//-------------------------------- map structs ---------------------------------

//	sets the default settings for the map after start-up
int	map_size_default_setting(t_sz *map_sz, t_sz size)
{
	map_sz->xposmw = WIDTH / 2;
	map_sz->yposmw = HEIGHT / 2;
	map_sz->zcentmw = Z;
	map_sz->xm_rot_deg = DEGREE_DEFAULT_X;
	map_sz->ym_rot_deg = DEGREE_DEFAULT_Y;
	map_sz->zm_rot_deg = DEGREE_DEFAULT_Z;
	map_sz->xm_size = size.xm_size;
	map_sz->ym_size = size.ym_size;
	map_sz->maxsz_x_p = map_sz->xposmw;
	map_sz->maxsz_x_m = map_sz->xposmw;
	map_sz->maxsz_y_p = map_sz->yposmw;
	map_sz->maxsz_y_m = map_sz->yposmw;
	map_sz->maxsz_z_p = Z;
	map_sz->maxsz_z_m = Z;
	return (EXIT_SUCCESS);
}

//------------------------------ coord structs --------------------------------

// this function set all important variables into struct to each point in a loop
int32_t	set_coord(t_window *window)
{
	t_coord	*coord;
	int		x_axis;
	int		y_axis;

	y_axis = 0;
	coord = NULL;
	ft_printf("\033[0;35mAssigning coordinate data...\033[0m\n");
	while (y_axis < window->map_sz.ym_size)
	{
		x_axis = 0;
		while (x_axis < window->map_sz.xm_size)
		{
			if (link_add_pt(&coord, x_axis, y_axis) == EXIT_FAILURE
				|| assign_coord_position(window, coord, x_axis,
					y_axis) == EXIT_FAILURE || update_mapsize(&window->map_sz,
					coord) == EXIT_FAILURE || assign_color
				(window, coord, x_axis, y_axis) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x_axis++;
		}
		y_axis++;
	}
	return (ft_set_after_y(coord, window), window->coord = coord, EXIT_SUCCESS);
}

//	assign the position of the points on the map and the middle of the window
int	assign_coord_position(t_window *window, t_coord *coord, int x, int y)
{
	double	round_x;
	double	round_y;

	round_x = 0.0;
	if (window->map_sz.xm_size % 2 == 1)
		round_x = 0.5;
	round_y = 0.0;
	if (window->map_sz.ym_size % 2 == 1)
		round_y = 0.5;
	coord->xm = -((window->map_sz.xm_size * window->start_size) / 2)
		+ ((x + round_x) * window->start_size);
	coord->ym = ((window->map_sz.ym_size * window->start_size) / 2)
		- ((y + round_y) * window->start_size);
	if (window->map[y][x][Z] >= INT_MIN && window->map[y][x][Z] <= INT_MAX)
	{
		coord->zm = window->map[y][x][Z] + window->map_sz.zm_offset;
		coord->xw = ft_round(coord->xm) + window->cent_xw;
		coord->yw = -ft_round(coord->ym) + window->cent_yw;
		coord->zw = ft_round(coord->zm);
		return (EXIT_SUCCESS);
	}
	return (perror("map assigning error"), EXIT_FAILURE);
}

//	assign the color to each coordinate, checks if htere is already a color
//	in the map given, if not, it sets the default color,depending on the value
//	of the z-axis
int	assign_color(t_window *window, t_coord *coord, int x, int y)
{
	if (window->map[y][x][COLOR] >= INT32_MIN
		&& window->map[y][x][COLOR] <= INT32_MAX)
	{
		if (window->map[y][x][COLOR] == 0)
		{
			if (coord->zm == 0)
				coord->color = COLOR_DEFAULT_CEN;
			else if (coord->zm == window->map_sz.zmcent_plus)
				coord->color = COLOR_DEFAULT_PLUS;
			else if (coord->zm == window->map_sz.zmcent_minus)
				coord->color = COLOR_DEFAULT_MIN;
			else if (coord->zm > Z)
				coord->color = find_color(COLOR_DEFAULT_CEN, COLOR_DEFAULT_PLUS,
						(float)(coord->zm) / (window->map_sz.zmcent_plus));
			else if (coord->zm < Z)
				coord->color = find_color(COLOR_DEFAULT_CEN, COLOR_DEFAULT_MIN,
						(float)(coord->zm) / (window->map_sz.zmcent_minus));
		}
		else
			coord->color = window->map[y][x][COLOR] << 8;
		coord->color += BRIGHTNESS_DEFAULT;
	}
	else
		return (perror("color assigning error"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
