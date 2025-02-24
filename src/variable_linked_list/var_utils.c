/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:33:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 20:26:06 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (prev_node)
				prev_node->next = prev_node->next->next;
			else
				sh->var_list = prev_node;
		}
		prev_node = iter_node;
		iter_node = iter_node->next;
	}
}

static void	var_iterator(t_var	*var, char *var_name, char **value, t_sh *sh)
{
	char	*old_value;

	old_value = ft_strdup("");
	add_galloc(old_value, 0, sh);
	while (var)
	{
		if (var->var_name)
		{
			if (ft_strncmp(var_name, var->var_name, \
				ft_strlen(var_name) + ft_strlen(var->var_name)) == 0)
			{
				*value = ft_strjoin(old_value, var->value);
				add_galloc(*value, 0, sh);
				return ;
			}
		}
		var = var->next;
	}
}

char	*get_value(t_var *var_iter, char *input, t_sh *sh)
{
	char	*value;
	char	*old_value;
	char	**var_names;

	var_names = ft_split(input, '$');
	old_value = ft_strdup("");
	add_galloc(old_value, 0, sh);
	add_galloc(var_names, 0, sh);
	value = ft_strdup("");
	add_galloc(value, 0, sh);
	while (*var_names)
	{
		add_galloc(*var_names, 0, sh);
		if (ft_get_env(*var_names, sh))
		{
			value = ft_strjoin(old_value, ft_get_env(*var_names, sh));
			add_galloc(value, 0, sh);
		}
		var_iterator(var_iter, *var_names, &value, sh);
		var_names++;
	}
	return (value);
}

static char	*var_return_cat(char *input, char *value, t_sh *sh)
{
	char	*return_str;
	char	*temp;

	temp = ft_substr(input, 1, ft_strlen(input) - 1);
	add_galloc(temp, 1, sh);
	return_str = ft_strjoin(value, temp);
	add_galloc(return_str, 1, sh);
	return (return_str);
}

t_token	**found_var(char *input, t_sh *sh)
{
	t_var	*var_iter;
	char	*value;
	char	*value_return;

	value = NULL;
	var_iter = sh->var_list;
	input++;
	if (ft_strncmp(input, "?", 1) == 0)
	{
		value_return = ft_itoa(sh->last_command);
		add_galloc(value_return, 0, sh);
		if (input[1])
		{
			value_return = var_return_cat(input, value_return, sh);
		}
		return (prepare_token_arr(value_return, sh));
	}
	value = get_value(var_iter, input, sh);
	if (value)
		return (prepare_token_arr(value, sh));
	return (NULL);
}
