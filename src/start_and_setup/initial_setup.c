/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:28:34 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/26 12:19:58 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//--------- function to initialize the coordinate data from the map ------------
//

//	function to read the map from the argument and process the data
//	map can be either inside project folder or within the test_maps
int	initialize_window_from_args(t_window *window, char *argv[])
{
	char	*file_path;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		file_path = ft_strjoin("test_maps/", argv[1]);
		if (!file_path)
			return (perror("Error loading maps"), EXIT_FAILURE);
		fd = open(file_path, O_RDONLY);
		free(file_path);
		if (fd == -1)
			return (close(fd), perror("Error opening file"), EXIT_FAILURE);
	}
	ft_printf("\033[0;35m\nReading map ...\033[0m\n");
	window->map = read_map_and_assign_data(fd);
	close(fd);
	if (!window->map)
		return (perror("Error reading map"), EXIT_FAILURE);
	ft_printf("\033[0;32m\nSuccesful!\033[0m\n");
	if (get_map_size(window) == EXIT_FAILURE
		|| set_default_window_data(window) == EXIT_FAILURE)
		return (perror("Error assiging map values to struct"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//	function to build the three dimensional array and save the map values there
int32_t	***read_map_and_assign_data(int fd)
{
	int32_t	***map;
	char	**collumn;
	int		row;
	int		collumn_counter;
	int		line;

	row = 0;
	collumn_counter = 0;
	map = NULL;
	while (1)
	{
		map = ft_realloc(map, (row + 1) * sizeof(int32_t **));
		if (!map)
			return (free_map_data(map, collumn, row));
		map[row] = NULL;
		line = read_line_into_collumn(fd, &collumn_counter, &collumn);
		if (check_for_map_errors(line, row, collumn_counter) == EXIT_FAILURE)
			return (free_map_data(map, collumn, row));
		else if (line == NO_NEW_LINE)
			return (map);
		map = assign(map, collumn, collumn_counter, &row);
		if (map == NULL)
			return (NULL);
	}
}

int	assign_color_to_struct(char *color, int32_t ***map_x_axis, int x)
{
	unsigned int	color_code;

	if (color)
	{
		color_code = convert_str_to_hex(color);
		if (color_code == EXIT_FAILURE)
		{
			while (x >= 0)
			{
				free((*map_x_axis)[x]);
				(*map_x_axis)[x] = NULL;
				x--;
			}
			return (EXIT_FAILURE);
		}
		(*map_x_axis)[x][COLOR] = (int32_t)color_code;
	}
	else
		(*map_x_axis)[x][COLOR] = Z;
	return (EXIT_SUCCESS);
}

//	function to assign the coordinate data from the map into 3-dimensional array
int	assign_map_values(int32_t ***map_x_axis, char **collumn, int line)
{
	char	*color;
	int		x;

	x = 0;
	while (collumn[x] != NULL)
	{
		(*map_x_axis)[x] = malloc(2 * sizeof(int));
		if (!(*map_x_axis)[x])
			return (EXIT_FAILURE);
		color = ft_strchr(collumn[x], ',');
		if (check_map_integer(map_x_axis, collumn, x, line) == EXIT_FAILURE
			|| assign_color_to_struct(color, map_x_axis, x) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*map_x_axis)[x][Z] = ft_atoi(collumn[x]);
		x++;
	}
	free_two_dimensional_array(collumn);
	return (EXIT_SUCCESS);
}

//	this function assigns all variable values of the map, which will change, but
//	only for the whole map at once, not every unique coordinate
int	get_map_size(t_window *window)
{
	t_sz		size;
	t_window	*temp;

	size.ym_size = 0;
	temp = window;
	while (temp->map[size.ym_size] != NULL)
		size.ym_size++;
	if (temp->map[0] != NULL)
	{
		size.xm_size = 0;
		while (temp->map[0][size.xm_size] != NULL)
			size.xm_size++;
	}
	if (map_size_default_setting(&window->map_sz, size) == EXIT_FAILURE
		|| find_highest_and_lowest(window) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
