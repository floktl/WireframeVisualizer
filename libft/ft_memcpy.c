/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 10:58:01 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:48:56 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	counter;
	char			*char_dst;
	char			*char_src;

	counter = 0;
	char_dst = (char *)dst;
	char_src = (char *)src;
	if (char_dst == NULL && char_src == NULL)
		return (NULL);
	while (counter < n)
	{
		char_dst[counter] = char_src[counter];
		counter++;
	}
	return (dst);
}

/*  int main(void)
{
	char dst[] = "fjfcfh";
	char src[] = "dsffads";
	ft_memcpy(dst, src, 2);
	printf("%s\n", dst);
	printf("%s\n", src);
	char dst2[] = "fjfcfh";
	char src2[] = "dsffads";
	memcpy(dst2, src2, 2);
	printf("%s\n", dst2);
	printf("%s\n", src2);

} */
