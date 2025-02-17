/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:33:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:40:07 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	var_iterator(t_var	*var, char *var_name, char **value)
{
	char	*old_value;

	while (var)
	{
		if (var->var_name)
		{
			if (ft_strncmp(var_name, var->var_name, \
				ft_strlen(var_name) + ft_strlen(var->var_name)) == 0)
			{
				old_value = *value;
				*value = ft_strjoin(old_value, var->value);
				free(old_value);
				return ;
			}
		}
		var = var->next;
	}
}

static char	*get_value(t_var *var_iter, char *input, t_sh *sh)
{
	char	*value;
	char	*old_value;
	char	**var_names;

	var_names = ft_split(input, '$');
	value = ft_strdup("");
	while (*var_names)
	{
		if (ft_get_env(*var_names, sh))
		{
			old_value = value;
			value = ft_strjoin(old_value, ft_get_env(*var_names, sh));
			free(old_value);
		}
		var_iterator(var_iter, *var_names, &value);
		var_names++;
	}
	return (value);
}

t_token	**found_var(char *input, t_sh *sh)
{
	t_var	*var_iter;
	char	*value;

	value = NULL;
	var_iter = sh->var_list;
	input++;
	if (ft_strncmp(input, "?", 1) == 0 && !input[1])
		return (prepare_token_arr(ft_itoa(sh->last_command), sh));
	value = get_value(var_iter, input, sh);
	printf("%s\n", value);
	if (value)
		return (prepare_token_arr(value, sh));
	return (NULL);
}
