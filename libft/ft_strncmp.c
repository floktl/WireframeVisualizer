/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:39:10 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:51:02 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	counter;

	counter = 0;
	while ((*s1 != '\0' || *s2 != '\0') && counter < n)
	{
		if (*s1 != *s2)
			return ((int)((unsigned char)*s1 - (unsigned char)*s2));
		s1++;
		s2++;
		counter++;
	}
	return (0);
}

/* int	main(void)
{
	const char str[] = "abcdef";
	const char str2[] = "abc\375xx";
	int i = 0;
	int j = 0;
	i = strncmp(str, str2, 5);
	printf("%d\n", i);
	j = ft_strncmp(str, str2, 5);
	printf("%d", j);
}*/
