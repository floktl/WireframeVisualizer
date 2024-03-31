/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematics2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:00:17 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/18 18:21:11 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//--------------------- using math.h would be way easier ----------------------
//

//	Approximation of arctangent function
int	ft_atan(int x)
{
	return (x - x * x * x / 3 + x * x * x * x * x / 5);
}

//	returns the radiant
double	radians(double degrees)
{
	return (degrees * PI / 180.0);
}

//	rounds a double or float datatype to an integer
int	ft_round(double num)
{
	if (num < 0)
		return ((int)(num - 0.5));
	else
		return ((int)(num + 0.5));
}

//	returns always a positive number, no matter if num is + or -
int	ft_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

//	function to convert an int to the range of 360 degrees
void	degree(int *rot)
{
	if (*rot >= 360)
		*rot -= 360;
	if (*rot < 0)
		*rot += 360;
}
