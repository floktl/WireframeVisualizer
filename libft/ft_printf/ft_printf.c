/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:27:14 by fkeitel           #+#    #+#             */
/*   Updated: 2024/01/03 15:14:01 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//This function implements a custom printf to format and print data to the
//standard output based on the provided format string and variable arguments.
int	ft_printf(const char *format, ...)
{
	int		counter;
	int		printed_chars;
	int		checkerror;
	va_list	arguments;

	counter = 0;
	printed_chars = 0;
	va_start (arguments, format);
	while (format[counter] != '\0')
	{
		if (format[counter] == '%')
		{
			checkerror = ft_checkcases(format[counter++ + 1], arguments);
			printed_chars += checkerror;
		}
		else if (printed_chars++ >= 0)
			checkerror = ft_putchar(format[counter], 1);
		if (checkerror == -1)
			return (-1);
		counter++;
	}
	va_end(arguments);
	return (printed_chars);
}
