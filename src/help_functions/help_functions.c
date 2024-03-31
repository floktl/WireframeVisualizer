/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:26 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 15:48:51 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//--------------------- additional small helper functions ----------------------
//

//	combines rgb and alpha(transparency) values into single color
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//	assigns  the highest and lowest value of the map (z_direction) as well
//	as the the distance to the map middlepoint in z direction
int	find_highest_and_lowest(t_window *map)
{
	int			x;
	int			y;

	map->map_sz.zmcent_plus = 0;
	map->map_sz.zmcent_minus = 0;
	y = 0;
	while (y < map->map_sz.ym_size)
	{
		x = 0;
		while (x < map->map_sz.xm_size)
		{
			if (map->map[y][x][Z] >= INT_MIN && map->map[y][x][Z] <= INT_MAX)
			{
				if (map->map[y][x][Z] > map->map_sz.zmcent_plus)
					map->map_sz.zmcent_plus = map->map[y][x][Z];
				if (map->map[y][x][Z] < map->map_sz.zmcent_minus)
					map->map_sz.zmcent_minus = map->map[y][x][Z];
			}
			else
				return (perror("value out of range"), EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

//	this function returns the zoom direction depending on the mouse position
double	check_zoom_direction(int map_middle, int zoom_position, double zoom)
{
	double	zoom_direction;

	if (map_middle < zoom_position)
		zoom_direction = ZOOM_M;
	else if (map_middle > zoom_position)
		zoom_direction = ZOOM_P;
	else
		zoom_direction = ZOOM_DEFAULT;
	if (zoom == ZOOM_M)
	{
		if (zoom_direction == ZOOM_P)
			zoom_direction = ZOOM_M;
		else if (zoom_direction == ZOOM_M)
			zoom_direction = ZOOM_P;
	}
	return (zoom_direction);
}

//	function to convert a string to a hexadezimal value
int32_t	convert_str_to_hex(char *hex_str)
{
	unsigned int	hex_value;
	unsigned int	digit_value;
	char			digit;
	int				i;

	i = 3;
	if (check_colorcode(hex_str, &digit) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (hex_str[i] != '\0')
	{
		if (digit >= '0' && digit <= '9')
			digit_value = digit - '0';
		else if (digit >= 'a' && digit <= 'f')
			digit_value = 10 + (digit - 'a');
		else if (digit >= 'A' && digit <= 'F')
			digit_value = 10 + (digit - 'A');
		else
		{
			ft_printf("color code not hexadezimal ");
			return (EXIT_FAILURE);
		}
		hex_value = (hex_value << 4) | digit_value;
		digit = hex_str[++i];
	}
	return (hex_value);
}

void	lstadd_back(t_man **lst, t_man *new)
{
	t_man	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}
