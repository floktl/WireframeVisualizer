/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:15:31 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/26 13:15:12 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (len == 0 || !s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sub_str = ft_calloc(1, 1);
		if (!sub_str)
			return (NULL);
		return (sub_str);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub_str = (char *)malloc(len);
	if (!sub_str)
		return (NULL);
	while (i <= len && s[i + start] != '\0')
	{
		sub_str[i] = s[i + start];
		i++;
	}
	return (sub_str[i] = '\0', sub_str);
}

/* int main()
{
	char str[] = "lorem ipsum dolor sit amet";
	char* target = ft_substr(str, 7, 10);
	printf("%s\n", target);
	free(target);
	return 0;
}*/
