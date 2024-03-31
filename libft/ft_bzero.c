/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:18:51 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/22 08:11:30 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	counter;
	char	*char_s;

	counter = 0;
	char_s = (char *)s;
	while (counter < n)
	{
		char_s[counter] = '\0';
		counter++;
	}
	s = char_s;
}

/* int main(void)
{
    char c[] = "asdgs";
    ft_bzero(c, 3); // Use bzero to set the first 3 bytes to null (0)
    printf("%s\n", c);
    return (0);
}*/
