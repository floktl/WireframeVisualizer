/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two_dimensional_array.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:57:41 by flo               #+#    #+#             */
/*   Updated: 2024/03/24 09:13:08 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	function to free an two dimensional array of chars
void	free_two_dimensional_array(char **param)
{
	int	count;

	count = 0;
	if (!param)
		return ;
	while (param[count])
	{
		free(param[count]);
		param[count] = NULL;
		count++;
	}
	free(param);
	param = NULL;
}
