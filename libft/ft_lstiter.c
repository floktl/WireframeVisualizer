/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:57:43 by fkeitel           #+#    #+#             */
/*   Updated: 2024/01/02 10:41:43 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(int))
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL)
		return ;
	current = lst;
	while (current != NULL)
	{
		next = current->next;
		f(current-> content);
		current = next;
	}
}
