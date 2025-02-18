/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:27 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/19 20:26:54 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr_next;

	if (!lst || !*lst || !del)
		return ;
	ptr = *lst;
	while (ptr)
	{
		del(ptr->content);
		ptr_next = ptr->next;
		free(ptr);
		ptr = ptr_next;
	}
	*lst = NULL;
}
