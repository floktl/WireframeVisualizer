/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_erros.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:54:00 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/26 12:56:52 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//------------------- functions to hadle map error cases -----------------------
//

//	this function checks, if the point on the map is an integer
int	check_map_integer(int32_t ***map_collumn, char **collumn, int x, int line)
{
	int		i;

	i = 0;
	if (collumn[x][0] == '+' || collumn[x][0] == '-')
		i++;
	while (collumn[x][i] && collumn[x][i] != ',')
	{
		if (collumn[x][i] < '0' || collumn[x][i] > '9')
		{
			x = 0;
			while ((*map_collumn)[x])
			{
				free((*map_collumn)[x]);
				(*map_collumn)[x] = NULL;
				(x)++;
			}
			ft_printf("Non-integer in line: %d pos: %d\n", line, x);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//	function to check for different map errors and prints the error
//	before ending the programm
int	check_for_map_errors(int line, int row, int collumn_counter)
{
	if (line == EXIT_FAILURE || (row == 0 && line == NO_NEW_LINE)
		|| (collumn_counter == 1) || line == MAP_NOT_SQUARED
		|| (row == 1 && line == NO_NEW_LINE))
	{
		ft_printf("\nMap ERROR!\n");
		if (row == 0 && line == NO_NEW_LINE)
			ft_printf("map empty\n");
		if (collumn_counter == 1)
			ft_printf("only one point on line %d\n", row + 1);
		if (line == MAP_NOT_SQUARED && collumn_counter != 1)
			ft_printf("map must be squared at line: %d\n", row + 1);
		if (row == 1 && line == NO_NEW_LINE)
			ft_printf("only one row\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//	function to check, if the colorcode is valid
int	check_colorcode(char *hex_str, char *digit)
{
	if (((hex_str[1] && hex_str[1] != '0') || !hex_str[1] || !hex_str[2])
		|| ((hex_str[2] && hex_str[2] != 'x')
			&& (hex_str[2] && hex_str[2] != 'X')))
	{
		ft_printf("color code should start with 0x ");
		return (EXIT_FAILURE);
	}
	if (hex_str[3] && hex_str[4] && ft_strlen(hex_str) <= 9)
		*digit = hex_str[3];
	else
	{
		ft_printf("color code unvalid ");
		if (ft_strlen(hex_str) > 9)
			ft_printf("->too long ");
		else if (!hex_str[3] || !!hex_str[4])
			ft_printf("->too short ");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
