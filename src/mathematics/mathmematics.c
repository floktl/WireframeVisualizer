/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathmematics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:59:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/19 13:38:24 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//	mathematical functions, as i dont use the math.h library
//

//	rounds a float number within a range given as parameter
float	round_float(float num, int range)
{
	float	factor;
	int		i;

	factor = 1.0;
	i = 0;
	while (i <= range)
	{
		factor *= 10.0;
		i++;
	}
	return ((float)((int)(num * factor + 0.5) / factor));
}

//	replace function for square root, why not, Math is fun!
//	Newton-Raphson Method
double	ft_sqrt(double a)
{
	double	x;
	double	next;

	x = a;
	while (1)
	{
		next = 0.5 * (x + a / x);
		if ((next - x) * (next - x) < EPSILON * EPSILON)
			break ;
		x = next;
	}
	return (x);
}

//	this function calculates a missing z variable for a point p(x; y; z)
//	input must be: A/cur(x; y; z) and B/next(x; y; z)
float	calc_z(t_coord *point_a, t_coord *point_b, float x_p, float y_p)
{
	float	d_ap;
	float	d_ab;
	float	t;
	float	z_p;

	d_ap = ft_sqrt((x_p - point_a->xw) * (x_p - point_a->xw)
			+ (y_p - point_a->yw) * (y_p - point_a->yw));
	d_ab = ft_sqrt((point_b->xw - point_a->xw) * (point_b->xw
				- point_a->xw) + (point_b->yw - point_a->yw)
			* (point_b->yw - point_a->yw));
	if (d_ab == 0)
		return ((float)point_a->zw);
	t = d_ap / d_ab;
	z_p = point_a->zw + t * ((float)point_b->zw - (float)point_a->zw);
	z_p = (float)(z_p - point_a->zw) / (point_b->zw - point_a->zw);
	return (z_p);
}
