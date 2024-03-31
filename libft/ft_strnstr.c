/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 18:11:47 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/30 19:49:50 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] == haystack[i + j] && i + j < len)
			{
				j++;
				if (needle[j] == '\0')
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}

// int main() {
//    const char* haystack = "aaabcabcd";
//    const char* needle = "aabc";
//    size_t len = strlen(haystack);

//    char* result = ft_strnstr(haystack, needle, 10);
//    printf("Needle found at position: %ld\n", result - haystack);
//	printf("Substring: %s\n", result);
//	char* result2 = strnstr(haystack, needle, 10);
//    printf("Needle found at position: %ld\n", result2 - haystack);
//	printf("Substring: %s\n", result2);
//    return 0;
//}
