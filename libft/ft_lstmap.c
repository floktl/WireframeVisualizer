/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:57:53 by fkeitel           #+#    #+#             */
/*   Updated: 2024/02/16 15:42:20 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(int), void (*del)(int))
// {
// 	t_list	*current;
// 	t_list	*new_list;
// 	void	*temp;

// 	if (!f || !lst)
// 		return (NULL);
// 	new_list = NULL;
// 	while (lst)
// 	{
// 		temp = f((int)lst->content);
// 		current = ft_lstnew((int)temp);
// 		if (current == NULL)
// 		{
// 			del((int)temp);
// 			ft_lstclear(&new_list, (*del));
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_list, current);
// 		lst = lst->next;
// 	}
// 	return (new_list);
//
