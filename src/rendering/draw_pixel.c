/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:39:28 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/24 14:37:54 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//------this function are for th eactually rendering the pixels the window-----
//

//	function to check if there is an error with the pixel position
int	check_error_pixel(t_coord *pt_a, t_coord *pt_b, int *x0, int *y0)
{
	static int	err = INT_MAX;

	if (err == INT_MAX)
		err = ft_abs(pt_b->xw - pt_a->xw) - ft_abs(pt_b->yw - pt_a->yw);
	if (*x0 == (pt_b->xw) && *y0 == pt_b->yw)
		return (err = INT_MAX, err);
	if ((2 * err) > -ft_abs(pt_b->yw - pt_a->yw))
	{
		err -= ft_abs(pt_b->yw - pt_a->yw);
		if (pt_a->xw < pt_b->xw)
			*x0 += 1;
		else
			*x0 -= 1;
	}
	else if ((2 * err) < abs(pt_b->xw - pt_a->xw))
	{
		err += ft_abs(pt_b->xw - pt_a->xw);
		if (pt_a->yw < pt_b->yw)
			*y0 += 1;
		else
			*y0 -= 1;
	}
	return (err);
}

//	function to find the color between two colors, with bitshifting,
//	adapt to each rgba part of the new color
int32_t	find_color(int32_t color_a, int32_t color_b, float t)
{
	t_color	color;

	if (color_a == color_b)
		return (color_a);
	color.color_a = color_a;
	color.color_b = color_b;
	color.r_a = (color.color_a >> 24) & 0xFF;
	color.g_a = (color.color_a >> 16) & 0xFF;
	color.b_a = (color.color_a >> 8) & 0xFF;
	color.a_a = color.color_a & 0xFF;
	color.r_b = (color.color_b >> 24) & 0xFF;
	color.g_b = (color.color_b >> 16) & 0xFF;
	color.b_b = (color.color_b >> 8) & 0xFF;
	color.a_b = color.color_b & 0xFF;
	color.r = (int32_t)(color.r_a + t * (color.r_b - color.r_a)) << 24;
	color.g = (int32_t)(color.g_a + t * (color.g_b - color.g_a)) << 16;
	color.b = (int32_t)(color.b_a + t * (color.b_b - color.b_a)) << 8;
	color.a = (int32_t)(color.a_a + t * (color.a_b - color.a_a));
	color.new_color = color.r | color.g | color.b | color.a;
	return (color.new_color);
}

//	function to check, if a point is on a line between two points:
//	((Px - Ax)(By - Ay) - (Py -Ay)(Bx - Ax)) == 0 (A = cur, B = next)
//	then a check if point is between the points A and B
//	laslty calculate the z axis of P with , and dislpay it
void	connect_points(t_window *window, t_coord *point_a, t_coord *point_b)
{
	float	z;
	int		x0;
	int		y0;
	int		err;
	int32_t	color_z;

	if (window == NULL || point_a == NULL || point_b == NULL)
		return ;
	x0 = point_a->xw;
	y0 = point_a->yw;
	while (1)
	{
		if (x0 > 0 && x0 < window->width && y0 > 0 && y0 < window->height)
		{
			z = calc_z(point_a, point_b, x0, y0);
			color_z = find_color(point_a->color, point_b->color, z);
			mlx_put_pixel(window->image, x0, y0, color_z);
		}
		err = check_error_pixel(point_a, point_b, &x0, &y0);
		if (err == INT_MAX)
			break ;
	}
}
