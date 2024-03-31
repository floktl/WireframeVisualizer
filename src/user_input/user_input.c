/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:11:17 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/18 18:57:53 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//	functions, that will handle all keypads and mouse inputs from the user
//

//	this function checks, if there is a change in the Z-Axis of the map
int	check_change_height(t_window *window)
{
	static double	prev_height = ZOOM_DEFAULT;

	if (window->map_sz.height_change == prev_height)
		return (NO_CHANGE);
	else
	{
		prev_height = window->map_sz.height_change;
		return (CHANGE);
	}
}

//	this function checks, if there is a change in the rotation from user input
int	check_change_in_rotation(t_window *window)
{
	static double	prev_rot_x = ZOOM_DEFAULT;
	static double	prev_rot_y = ZOOM_DEFAULT;
	static double	prev_rot_z = ZOOM_DEFAULT;

	if (window->map_sz.xm_rot_deg == prev_rot_x
		&& window->map_sz.ym_rot_deg == prev_rot_y
		&& window->map_sz.zm_rot_deg == prev_rot_z)
		return (NO_CHANGE);
	else
	{
		prev_rot_x = window->map_sz.xm_rot_deg;
		prev_rot_y = window->map_sz.ym_rot_deg;
		prev_rot_z = window->map_sz.zm_rot_deg;
		return (CHANGE);
	}
}
