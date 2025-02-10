/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:54 by jtinaut-          #+#    #+#             */
/*   Updated: 2024/10/09 16:19:37 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_ft_strchr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}

char	*ft_trimmer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] != '\0')
			str[i + 1] = '\0';
		i++;
	}
	return (str);
}

t_gnl	*ft_addnode(t_gnl **list, char *text)
{
	t_gnl	*iteri;
	t_gnl	*new_node;
	char	*new_text;

	iteri = *list;
	if (!text)
		return (NULL);
	if (ft_memorymanager((void *)&new_text, BUFFER_SIZE))
		return (NULL);
	new_node = malloc(sizeof(t_gnl));
	if (!new_node)
		return (NULL);
	ft_strcpy(new_text, text);
	free(text);
	new_node->text = new_text;
	new_node->next = NULL;
	if (!iteri)
		return (*list = new_node);
	while (iteri->next)
		iteri = iteri->next;
	iteri->next = new_node;
	return (new_node);
}

int	ft_listlen(t_gnl *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;
	int	j;

	if (!src)
	{
		dst = NULL;
		return (dst);
	}
	i = 0;
	j = 0;
	if (dst[0])
	{
		while (dst[i])
			i++;
	}
	while (src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ft_ft_strchr(src));
}
