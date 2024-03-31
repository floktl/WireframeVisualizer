/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:25:39 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:48:49 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*z;
	unsigned char		uc;
	size_t				counter;

	uc = (unsigned char)c;
	z = (const unsigned char *)s;
	counter = 0;
	while (counter++ < n)
	{
		if (*z == uc)
			return ((void *)z);
		z++;
	}
	return (0);
}

/* int	main(void) {
	const char str[] = "/|\x12\xff\x09\x42\2002\42|\\";
	char search_char = '\200';
	size_t search_size = 10;
	const void *result = ft_memchr(str, search_char, search_size);
	size_t index = (size_t)((const char *)result - str);
	printf("'%c' found at index %zu\n", search_char, index);
	return 0;
}*/
