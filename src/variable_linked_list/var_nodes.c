/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:33:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:38:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_name(char **input, t_sh *sh)
{
	char	*var_name;
	size_t	i;

	i = 0;
	var_name = galloc(((ft_strlen(*input) - \
	ft_strlen(ft_strchr(*input, '='))) + 1) * sizeof(char), 0, sh);
	while (**input && **input != '=')
		var_name[i++] = *(*input)++;
	(*input)++;
	return (var_name);
}

static void	add_var_extended(char *input, t_var *var_node, t_sh *sh)
{
	if (ft_strchr(input, '"') || ft_strchr(input, '\''))
	{
		var_node->value = extract_between_chars(sh->line, '\"', sh);
		if (!var_node->value)
			var_node->value = extract_between_chars(sh->line, '\'', sh);
		if (!var_node->value)
			var_node->value = galloc(1, 0, sh);
	}
	else
	{
		var_node->value = ft_strdup(input);
		add_galloc(var_node->value, 0, sh);
	}
}

void	add_var(char *input, t_sh *sh)
{
	t_var	*var_node;
	char	*var_name;

	var_node = sh->var_list;
	if (*input == '=')
		return ;
	var_name = get_var_name(&input, sh);
	while (var_node)
	{
		if (var_node->var_name && ft_strncmp(var_name, var_node->var_name, \
				ft_strlen(var_name) + ft_strlen(var_node->var_name)) == 0)
			break ;
		var_node = var_node->next;
	}
	if (!var_node)
	{
		var_node = var_addnode(sh);
		var_node->var_name = var_name;
	}
	add_var_extended(input, var_node, sh);
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
	var_node = galloc(sizeof(t_var), 0, sh);
	var_node->next = NULL;
	var_node->var_name = NULL;
	var_node->value = NULL;
	return (var_node);
}
