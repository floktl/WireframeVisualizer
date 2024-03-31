/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:33:22 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/30 19:46:35 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_places(unsigned int n)
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

static int	check_negativ(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char			*c;
	int				num_digits;
	int				i;
	unsigned int	num;

	if (check_negativ(n) == 1)
		num = n * (-1);
	else
		num = n;
	num_digits = num_places(num) + check_negativ(n);
	c = (char *)malloc(num_digits + 1);
	if (c == NULL)
		return (NULL);
	if (check_negativ(n) == 1)
		c[0] = '-';
	i = num_digits - 1;
	while (i >= check_negativ(n))
	{
		c[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	c[num_digits] = '\0';
	return ((char *)c);
}
/*
int main(void)
{
    int n = -18376789;
    char *s;

    s = ft_itoa(-100);
    printf("%s\n", s);
    free(s);
    return 0;
}*/
