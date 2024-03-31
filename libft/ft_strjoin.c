/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:13:06 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:50:44 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*conc_str;
	int		counter;
	int		counter_2;

	counter = 0;
	counter_2 = 0;
	conc_str = malloc((int)ft_strlen(s1) + (int)ft_strlen(s2) + 1);
	if (!s1 || !s2)
		return (NULL);
	if (conc_str == NULL)
		return (NULL);
	while (s1[counter] != '\0')
	{
		conc_str[counter] = s1[counter];
		counter++;
	}
	while (s2[counter_2] != '\0')
	{
		conc_str[counter_2 + counter] = s2[counter_2];
		counter_2++;
	}
	conc_str[counter + counter_2] = '\0';
	return (conc_str);
}

/* int main()
{
	char str1[] = "lorem ipsum";
	char str2[] = "dolor sit amet";
	char* target = ft_strjoin(str1, str2);
	printf("%s", target);
	return 0;
}*/
