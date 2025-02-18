/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:33:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:31 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* TODO: check code for leaks and use galloc */
void	add_var(char *input, t_sh *sh)
{
	t_var	*var_node;
	int		i;

	if (*input == '=')
		return ;
	var_node = var_addnode(sh);
	var_node->var_name = galloc(((ft_strlen(input) - \
		ft_strlen(ft_strchr(input, '='))) + 1) * sizeof(char), sh);
	i = 0;
	while (*input && *input != '=')
		var_node->var_name[i++] = *(input++);
	input++;
	if (ft_strchr(input, '"') || ft_strchr(input, '\''))
		var_node->value = extract_between_chars(sh->line, '\"', sh);
	else
		var_node->value = ft_strdup(input);
}

void	var_delnode(char *var_name, t_sh *sh)
{
	t_var	*iter_node;
	t_var	*prev_node;

	iter_node = sh->var_list;
	prev_node = NULL;
	while (iter_node)
	{
		if (iter_node->var_name && \
			ft_strncmp(var_name, iter_node->var_name, ft_strlen(var_name)) == 0)
		{
			//gfree(iter_node->var_name, sh);
			//gfree(iter_node->value, sh);
			//gfree(iter_node, sh);
			if (prev_node)
				prev_node->next = prev_node->next->next;
			else
				sh->var_list = prev_node;
		}
		prev_node = iter_node;
		iter_node = iter_node->next;
	}
}

t_var	*var_addnode(t_sh *sh)
{
	t_var	*new_node;
	t_var	*node_iter;

	new_node = NULL;
	new_node = var_init(new_node, sh);
	node_iter = sh->var_list;
	while (node_iter->next)
		node_iter = node_iter->next;
	node_iter->next = new_node;
	return (new_node);
}

t_var	*var_init(t_var *var_node, t_sh *sh)
{
	var_node = galloc(sizeof(t_var), sh);
	var_node->next = NULL;
	var_node->var_name = NULL;
	var_node->value = NULL;
	return (var_node);
}
