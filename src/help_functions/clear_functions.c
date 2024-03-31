/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:14:49 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 15:16:23 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//-------------- functions to prevent leaks and for cleaning up ----------------
//

//	function for freeing all values within a stack
void	free_map_coordinates(t_coord **stack)
{
	t_coord	*head;
	t_coord	*tmp;

	if (!stack)
		return ;
	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}

//	function to reset all pixelsof the window to its default colors
void	clear_image(t_window *window, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < window->mlx->height)
	{
		x = 0;
		while (x < window->mlx->width)
		{
			mlx_put_pixel(window->image, x, y, color);
			x++;
		}
		y++;
	}
}

//	function to free an 3 dimensional array of integers
void	free_map(int32_t ***map)
{
	int	y;
	int	x;

	if (!map)
		return ;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != NULL)
		{
			free(map[y][x]);
			map[y][x] = NULL;
			x++;
		}
		free(map[y]);
		map[y] = NULL;
		y++;
	}
	free(map);
	map = NULL;
}

int32_t	***free_map_data(int32_t ***map, char **collumn, int row)
{
	map[row] = NULL;
	free_two_dimensional_array(collumn);
	free_map(map);
	return (NULL);
}

//	function to free the manual
void	free_manual(t_man **stack)
{
	t_man	*tmp;

	while (*stack)
	{
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp->string);
		tmp->string = NULL;
		free(tmp);
		tmp = NULL;
	}
}
