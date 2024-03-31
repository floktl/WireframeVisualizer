/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 09:16:53 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/25 10:45:11 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//------------------------- functions to read the map --------------------------
//

// function to assign the map data to the array and allocate new memory
int32_t	***assign(int32_t ***map, char **collumn, int collumn_counter, int *row)
{
	map[*row] = malloc(sizeof(int32_t *) * (collumn_counter + 1));
	if (!map[*row])
		return (free_map_data(map, collumn, *row));
	map[*row][collumn_counter] = NULL;
	if (assign_map_values(&map[*row], collumn, *row) == EXIT_FAILURE)
	{
		free(map[*row]);
		map[*row] = NULL;
		ft_printf("at line %d col %d\n", *row + 1, collumn_counter);
		return (free_map_data(map, collumn, *row));
	}
	(*row)++;
	return (map);
}

//	function to get a new line with get next line, cut out unecessary data
//	and save the points in a two dimensional array
int	read_line_into_collumn(int fd, int *collumn_counter, char ***collumn)
{
	char		*line;
	static int	x_counter = 0;
	char		*line_without_new_line;

	line = get_next_line(fd);
	if (!line)
		return ((*collumn) = NULL, NO_NEW_LINE);
	line_without_new_line = ft_strtrim(line, "\n");
	if (line_without_new_line)
	{
		free(line);
		line = line_without_new_line;
	}
	*collumn = ft_split(line, ' ');
	free(line);
	line = NULL;
	if (!(*collumn))
		return (EXIT_FAILURE);
	*collumn_counter = 0;
	delete_spaces(collumn_counter, collumn);
	if (x_counter == 0)
		x_counter = *collumn_counter;
	if (x_counter != *collumn_counter)
		return (MAP_NOT_SQUARED);
	return (NEW_LINE);
}

// function to delete spaces from an two dimensional array after using ft_split
void	delete_spaces(int *collumn_counter, char ***collumn)
{
	char		*collumn_without_spaces;

	while ((*collumn)[*collumn_counter])
	{
		collumn_without_spaces = ft_strtrim((*collumn)[*collumn_counter], " ");
		free((*collumn)[*collumn_counter]);
		(*collumn)[*collumn_counter] = NULL;
		if (collumn_without_spaces)
		{
			(*collumn)[*collumn_counter] = collumn_without_spaces;
		}
		(*collumn_counter)++;
	}
	(*collumn)[*collumn_counter] = NULL;
}
