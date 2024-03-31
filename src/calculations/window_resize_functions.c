/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:45:17 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 20:34:27 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//---------------------- functions for window rezising ------------------------
//

//	this functions updates the window struct, when the window size is changed
void	ft_resize(int width, int height, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (width != window->width || height != window->height)
		mlx_resize_image(window->image, width, height);
	else
		return ;
	window->width = width;
	window->height = height;
	window->cent_xw = width / 2;
	window->cent_yw = height / 2;
	window->map_sz.xm_offset = window->map_sz.xposmw - window->cent_xw;
	window->map_sz.ym_offset = window->cent_yw - window->map_sz.yposmw;
	window->max_zoom_size = (window->mlx->width * window->mlx->height)
		* MAX_MAP_SIZE;
	window->min_zoom_size = (window->mlx->width * window->mlx->height)
		/ MIN_MAP_SIZE;
	check_if_map_is_outside_window(window);
}

void	check_if_map_is_outside_window(t_window *window)
{
	t_coord		*coord;

	if ((window->map_sz.maxsz_x_m) > (window->width - MARGIN)
		|| (window->map_sz.maxsz_y_p) > (window->height - MARGIN))
	{
		window->map_sz.xposmw = window->width / 2;
		window->map_sz.yposmw = window->height / 2;
		coord = window->coord;
		while (coord != NULL)
		{
			rotation_calc(window, coord);
			coord = coord->next;
		}
	}
}
