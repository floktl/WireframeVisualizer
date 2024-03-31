/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_datatypes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:48:07 by fkeitel           #+#    #+#             */
/*   Updated: 2024/01/03 15:13:55 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//
//function for checking which dataformat is given as argument
//

//his function analyzes the format specifier and dispatches the corresponding-
//argument to the appropriate printing function, handling different data types-
//like character, integer, string, pointer, unsigned integer, and hexadecimal.
int	ft_checkcases(const char format, va_list argument)
{
	unsigned long	value;

	if (format == 'c')
		return (ft_putchar(va_arg(argument, int), 1));
	else if (format == 'd' || format == 'i')
		return (put_i(va_arg(argument, int), 0));
	else if (format == 's')
		return (ft_printstr(va_arg(argument, char *), 0));
	else if (format == 'p')
		return (put_p(argument));
	else if (format == 'u')
		return (put_u(va_arg(argument, unsigned int)));
	else if (format == '%')
		return (ft_putchar('%', 1));
	else if (format == 'x' || format == 'X')
	{
		value = va_arg(argument, unsigned int);
		return (put_hex(&value, format, 0));
	}
	return (0);
}
