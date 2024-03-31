/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:32:18 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/17 11:03:29 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trim;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	str_trim = malloc(end - start + 2);
	if (!str_trim)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		str_trim[i] = s1[start];
		i++;
		start++;
	}
	str_trim[i] = '\0';
	return (str_trim);
}

/* int main()
{
	char s1[] = "qqaqqqa";
	char set[] = "qqa";
	char* target = ft_strtrim(s1, set);
	printf("%s", target);
	free(target);
	return 0;
} */
