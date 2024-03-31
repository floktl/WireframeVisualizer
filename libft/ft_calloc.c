/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:58:37 by fkeitel           #+#    #+#             */
/*   Updated: 2023/10/18 16:48:16 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

/* int	main(void)
{
	size_t num_elements = 5;
	size_t element_size = sizeof(int);
	int *arr = (int *)ft_calloc(num_elements, element_size);
	if (arr == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
	}
	for (size_t i = 0; i < num_elements; i++) {
		arr[i] = i * 10;
	}
	printf("Allocated array: ");
	for (size_t i = 0; i < num_elements; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
} */
