/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:21:26 by flo               #+#    #+#             */
/*   Updated: 2024/03/25 16:25:47 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//	function to remove the manual from the window and replace it
void	remove_manual_from_window(t_window *window)
{
	t_man		*initial_manual;

	initial_manual = window->manual;
	while (window->manual)
	{
		mlx_delete_image(window->mlx, window->manual->str);
		window->manual = window->manual->next;
	}
	window->manual = initial_manual;
	window->man = mlx_put_string(window->mlx, "For <I> Manual", 8, 8);
}

//	this function sets the map to the middle of the window
void	set_map_to_middle(t_window *window)
{
	window->map_sz.xposmw = window->width / 2;
	window->map_sz.yposmw = window->height / 2;
	window->map_sz.zcentmw = Z;
	window->map_sz.xm_rot_deg = DEGREE_DEFAULT_X;
	window->map_sz.ym_rot_deg = DEGREE_DEFAULT_Y;
	window->map_sz.zm_rot_deg = DEGREE_DEFAULT_Z;
}

// function to print the manual given as a txt.file to the window
void	print_manual(t_window *window)
{
	int		y;
	int		distance;
	t_man	*temp;

	temp = window->manual;
	y = 8;
	distance = 16;
	mlx_delete_image(window->mlx, window->man);
	while (temp)
	{
		temp->str = mlx_put_string(window->mlx, temp->string, 8, y);
		temp = temp->next;
		y += distance;
	}
}
