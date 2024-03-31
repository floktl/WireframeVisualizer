/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:39:23 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/30 19:48:54 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_char(char c, int fd)
{
	write(fd, &c, 1);
}

static int	num_place(unsigned int n)
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

void	ft_putnbr_fd(int n, int fd)
{
	int				num_digits;
	int				i;
	unsigned int	num;
	char			digit_buffer[11];

	if (n < 0)
	{
		num = -n;
		put_char('-', fd);
	}
	else
		num = n;
	num_digits = num_place(num);
	i = num_digits - 1;
	while (i >= 0)
	{
		digit_buffer[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	write(fd, digit_buffer, num_digits);
}

/*#include "libft.h"
#include <unistd.h>

int main()
{
    int num1 = 12345;
    int num2 = -6789;

    ft_putnbr_fd(num1, 1); // Print num1 to standard output
    write(1, "\n", 1);    // Print a newline
    ft_putnbr_fd(num2, 1); // Print num2 to standard output
    write(1, "\n", 1);    // Print a newline

    return 0;
}*/
