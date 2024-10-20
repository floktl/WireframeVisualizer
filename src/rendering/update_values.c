/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 08:24:45 by fkeitel           #+#    #+#             */
/*   Updated: 2024/10/20 07:59:46 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//
//------- this functions update the map values after changing parameters -------
//

//this function updates all important variables to each point in map
int32_t	update_coord(t_win_data *window, int x_offset, int y_offset)
{
	t_coord		*temp;

	temp = window->coord;
	window->map_sz.xm_offset += x_offset;
	window->map_sz.ym_offset += y_offset;
	window->map_sz.xposmw += x_offset;
	window->map_sz.yposmw += y_offset;
	calculate_zoom_pos(window);
	calculate_height_change(window);
	reset_map_size(window);
	while (temp != NULL)
	{
		temp->xw += x_offset;
		temp->yw += y_offset;
		temp->zm *= window->map_sz.height_change;
		zoom_calc(window, temp);
		rotation_calc(window, temp);
		update_mapsize(&window->map_sz, temp);
		print_stacks(window, temp);
		temp = temp->next;
	}
	window->map_sz.height_change = HEIGHT_DEFAULT;
	window->zoom = ZOOM_DEFAULT;
	return (EXIT_SUCCESS);
}

// function to calculate the max and min change of the z_axis of the map
int	calculate_height_change(t_win_data *window)
{
	int	z_size;

	if (window->map_sz.height_change == HEIGHT_DEFAULT)
		return (NO_CHANGE);
	z_size = (window->map_sz.maxsz_z_p
			- window->map_sz.maxsz_z_m) * window->map_sz.height_change;
	if (window->map_sz.height_change > HEIGHT_DEFAULT
		&& ((z_size > window->height * 2)
			|| (z_size > window->width * 2)))
		window->map_sz.height_change = HEIGHT_DEFAULT;
	if (window->map_sz.height_change < HEIGHT_DEFAULT
		&& z_size == Z)
		window->map_sz.height_change = HEIGHT_DEFAULT;
	return (CHANGE);
}

//	function to set the map size to the default values
void	reset_map_size(t_win_data *window)
{
	window->map_sz.maxsz_x_p = window->map_sz.xposmw;
	window->map_sz.maxsz_x_m = window->map_sz.xposmw;
	window->map_sz.maxsz_y_p = window->map_sz.yposmw;
	window->map_sz.maxsz_y_m = window->map_sz.yposmw;
	window->map_sz.maxsz_z_p = Z;
	window->map_sz.maxsz_z_m = Z;
}

//	update the furthest points of the map from the map center
int	update_mapsize(t_map_data *map_sz, t_coord *temp)
{
	if ((map_sz->maxsz_x_p) < temp->xw)
		map_sz->maxsz_x_p = temp->xw;
	if (map_sz->maxsz_x_m > temp->xw)
		map_sz->maxsz_x_m = temp->xw;
	if (map_sz->maxsz_y_p > temp->yw)
		map_sz->maxsz_y_p = temp->yw;
	if (map_sz->maxsz_y_m < temp->yw)
		map_sz->maxsz_y_m = temp->yw;
	if (map_sz->maxsz_z_p < temp->zm)
		map_sz->maxsz_z_p = temp->zm;
	if (map_sz->maxsz_z_m > temp->zm)
		map_sz->maxsz_z_m = temp->zm;
	map_sz->map_area = (map_sz->maxsz_x_p - map_sz->maxsz_x_m)
		* (map_sz->maxsz_y_p + map_sz->maxsz_y_m);
	return (EXIT_SUCCESS);
}
