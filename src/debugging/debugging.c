/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:25:40 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/22 17:54:55 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//------------------------------- debug functions ------------------------------
//

//	this functions are usefool tools for debugging, they are not necessary for
//	the functionality, but they still pass norminette

//	terminal output colors
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

//	printing the coordinates and other useful data of each point
int	print_coord_data(t_window *window, t_coord *current, const char *color)
{
	*window = *window;
	ft_printf("%s", color);
	ft_printf("%d|%d ", current->pos_xm, current->pos_ym);
	ft_printf("Pos map: %d|%d|%d ", ft_round(current->xm),
		ft_round(current->ym), ft_round(current->zm));
	ft_printf("zoom: %d ", ft_round(window->zoom));
	ft_printf("Pos window: %d|%d|%d ", current->xw, current->yw, current->zw);
	ft_printf("offset map: %d|%d|%d ", ft_round(window->map_sz.xm_offset),
		ft_round(window->map_sz.ym_offset), ft_round(window->map_sz.zm_offset));
	ft_printf("map pos win: %d|%d|%d ", window->map_sz.xposmw,
		window->map_sz.yposmw, window->map_sz.zcentmw);
	ft_printf("deg to cen map: %d|%d|%d ", window->map_sz.xm_rot_deg,
		window->map_sz.ym_rot_deg, window->map_sz.zm_rot_deg);
	ft_printf("max sz map: x: %d|%d y: %d|%d z: %d|%d ",
		(window->map_sz.maxsz_x_p), (window->map_sz.maxsz_x_m),
		(window->map_sz.maxsz_y_p), (window->map_sz.maxsz_y_m),
		(window->map_sz.maxsz_z_p), (window->map_sz.maxsz_z_m));
	ft_printf("wsz: %d|%d ", window->width, window->height);
	ft_printf("color: 0x%X ", current->color);
	return (NO_CHANGE);
}

//	prints the map of the 3 dimensional array
void	print_map(int32_t ***map)
{
	int	i;
	int	j;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i] != NULL)
	{
		ft_printf("Map[%d]:\n", i);
		j = 0;
		while (map[i][j] != NULL)
		{
			ft_printf("  Line %d: ", j);
			ft_printf("%d ", map[i][j][Z]);
			ft_printf("%X", map[i][j][COLOR]);
			ft_printf("\n");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

//	prints the values of all coordinates (distances, color, degree, position...)
void	print_stacks(t_window *window, t_coord *current)
{
	const char	*color;
	int			row_number;

	if (window->debug_mode == OFF)
		return ;
	color = COLOR_RESET;
	row_number = 1;
	if (current->next != NULL && (current->next->pos_xm - 1) == 1)
		ft_printf("\n");
	if (row_number++ % 2 == 0)
		color = COLOR_MAGENTA;
	else
		color = COLOR_RESET;
	ft_printf("\n");
	print_coord_data(window, current, color);
	ft_printf("\n");
	ft_printf("%s\n\n", COLOR_RESET);
}

//	printing a line between two points, which can used for debugging
void	print_debug_point_1(t_window *window)
{
	if (window->debug_mode == OFF)
		return ;
	window->debug_point_1.xw = window->map_sz.xposmw - 500;
	window->debug_point_1.yw = window->map_sz.yposmw;
	window->debug_point_1.zw = Z;
	window->debug_point_2.xw = window->map_sz.xposmw + 500;
	window->debug_point_2.yw = window->map_sz.yposmw;
	window->debug_point_2.zw = Z;
	window->debug_point_1.color = YELLOW + BRIGHTNESS_DEFAULT;
	window->debug_point_2.color = YELLOW + BRIGHTNESS_DEFAULT;
	connect_points(window, &window->debug_point_1, &window->debug_point_2);
}

//	printing a line between two points, which can used for debugging
void	print_debug_point_2(t_window *window)
{
	if (window->debug_mode == OFF)
		return ;
	window->debug_point_3.xw = window->map_sz.xposmw;
	window->debug_point_3.yw = window->map_sz.yposmw - 500;
	window->debug_point_3.zw = Z;
	window->debug_point_4.xw = window->map_sz.xposmw;
	window->debug_point_4.yw = window->map_sz.yposmw + 500;
	window->debug_point_4.zw = Z;
	window->debug_point_3.color = RED + BRIGHTNESS_DEFAULT;
	window->debug_point_4.color = RED + BRIGHTNESS_DEFAULT;
	connect_points(window, &window->debug_point_3, &window->debug_point_4);
}

		//if (current->next != NULL)
		//	printf("nx: %d|%d\t", current->next->pos_xm,
		//		current->next->pos_ym);
		//else
		//	printf("nx:  |  \t");
		//if (current->before != NULL)
		//	printf("bx: %d|%d\t", current->before->pos_xm,
		//		current->before->pos_ym);
		//else
		//	printf("bx:  |  \t");
		//if (current->next_y != NULL)
		//	printf("ny; %d|%d\t", current->next_y->pos_xm,
		//		current->next_y->pos_ym);
		//else
		//	printf("ny:  | \t");

	//if (current->before_y != NULL)
	//	printf("by: %d|%d\t", current->before_y->pos_xm,
	//		current->before_y->pos_ym);
	//else
	//	printf("by;  | \t");
