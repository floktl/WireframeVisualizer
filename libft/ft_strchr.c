/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:03:40 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:50:31 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	str_len;

	str_len = ft_strlen(s);
	while (str_len >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		str_len--;
	}
	return (NULL);
}

/*  int main (void)
{
   const char str[] = "https://www.tutorialspoint.com";
   char *ret;
   char *ret2;

   ret = ft_strchr(str, 't' + 256);
   ret2 = strchr(str, 't' + 256);
   printf("%s\n", ret);
   printf("%s\n", ret2);
   return(0);
}*/
