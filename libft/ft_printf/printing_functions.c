/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:26:24 by fkeitel           #+#    #+#             */
/*   Updated: 2024/01/03 15:14:11 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//
//functions for the actual printing
//

//This function prints string to standard output, returns num of chars printed
int	ft_printstr(char *str, int counter)
{
	if (!str)
	{
		if (ft_printstr("(null)", 0) == -1)
			return (-1);
		return (6);
	}
	while (str[counter])
	{
		if (ft_putchar(str[counter], 1) == -1)
			return (-1);
		counter++;
	}
	return (counter);
}

//This function writes a single character to the standard output
int	ft_putchar(int c, int counter)
{
	if (write(1, &c, counter) == -1)
		return (-1);
	return (1);
}
