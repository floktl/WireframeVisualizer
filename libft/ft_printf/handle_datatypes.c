/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_datatypes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:39:23 by fkeitel           #+#    #+#             */
/*   Updated: 2024/01/03 15:14:06 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

//
//Functions for handling different data formats (u, i, x, X, p)
//

//This function calculates and returns number of digits in unsigned integer n
int	num_place(unsigned int n)
{
	if (n < 0)
		return (0);
	if (n < 10)
		return (1);
	if (n < 100)
		return (2);
	if (n < 1000)
		return (3);
	if (n < 10000)
		return (4);
	if (n < 100000)
		return (5);
	if (n < 1000000)
		return (6);
	if (n < 10000000)
		return (7);
	if (n < 100000000)
		return (8);
	if (n < 1000000000)
		return (9);
	return (10);
}

//This function prints an integer n in base 10 format to the standard output,-
// returns total num of chars printed, incl. negative sign for negative nums.
int	put_i(int n, int counter)
{
	int				num_digits;
	int				i;
	unsigned int	num;
	char			digit_buffer[11];

	if (n < 0 && counter++ >= 0)
	{
		num = -n;
		if (ft_putchar('-', 1) == -1)
			return (-1);
	}
	else
		num = n;
	num_digits = num_place(num);
	counter += num_digits;
	i = num_digits - 1;
	while (i >= 0)
	{
		digit_buffer[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	if (write(1, digit_buffer, num_digits) == -1)
		return (-1);
	return (counter);
}

//This function prints number pointed to by hexadecimal in hexadecimal format, -
//in uppercase (X) or lowercase (x), and returns the total num of chars printed
int	put_hex(unsigned long *hexadecimal, int upper_lower, int counter)
{
	char			*hex_chars;
	char			address_str[17];
	int				i;
	unsigned int	index;

	if (upper_lower == 'x')
		hex_chars = "0123456789abcdef";
	else if (upper_lower == 'X')
		hex_chars = "0123456789ABCDEF";
	if (*hexadecimal == 0)
		return (ft_printstr("0", 0));
	i = sizeof(unsigned long) * 2 - 1 ;
	index = 0;
	while (i >= 0)
	{
		if (((hex_chars[(*hexadecimal >> (i * 4)) & 0xF]) != '0' \
			|| index > 0 || i == 0) && counter++ >= 0)
			address_str[index++] = hex_chars[(*hexadecimal >> (i * 4)) & 0xF];
		i--;
	}
	address_str[index] = '\0';
	counter = ft_printstr(address_str, 0);
	return (counter);
}

//This funct. recursiv. prints unsign. int base 10, returns num of chars printed
int	put_u(unsigned int n)
{
	int	counter;
	int	check;

	counter = 0;
	if (n >= 10)
	{
		check = put_u(n / 10);
		if (check == -1)
			return (-1);
		counter += check;
	}
	if (ft_putchar((n % 10 + '0'), 1) == -1)
		return (-1);
	counter++;
	return (counter);
}

//This function formats, prints a void* pointer argument in hexadecimal format
//including the "0x" prefix, and returns the total number of characters printed
int	put_p(va_list argument)
{
	int		check;
	size_t	*ptr;
	int		counter;

	counter = 0;
	ptr = va_arg(argument, void *);
	check = ft_printstr("0x", 0);
	if (check == -1)
		return (-1);
	counter += check;
	check = put_hex((unsigned long *)&ptr, 'x', 0);
	if (check == -1)
		return (-1);
	return (counter + check);
}
