/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:00:03 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/16 10:23:07 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	counter;
	size_t	dest_len;

	counter = 0;
	dest_len = 0;
	while (dst[dest_len] != '\0' && dest_len < dstsize)
		dest_len++;
	counter = dest_len;
	while (*src != '\0' && counter + 1 < dstsize)
		dst[counter++] = *src++;
	if (counter < dstsize)
		dst[counter] = '\0';
	while (*src != '\0')
	{
		counter++;
		src++;
	}
	return (counter);
}

/* int main() {
	char destination[20] = "Hello, ";
	const char* source = "";
	size_t result = strlcat(destination, source, sizeof(destination));
	printf("Result: %zu\n", result);
	printf("Concatenated String: %s\n", destination);
	return 0;
}*/
