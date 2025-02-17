/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:33:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 19:01:35 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*iter_var(t_var *var_iter, char *input, t_sh *sh)
{
	char	*value;
	char	*old_value;
	char	**var_names;
	t_var	*start;

	var_names = ft_split(input, '$');
	value = ft_strdup("");
	start = var_iter;
	while (*var_names)
	{
		if (ft_get_env(*var_names, sh))
		{
			old_value = value;
			value = ft_strjoin(old_value, ft_get_env(*var_names, sh));
			free(old_value);
		}
		var_iter = start;
		while (var_iter)
		{
			if (var_iter->var_name)
			{
				if (ft_strncmp(*var_names, var_iter->var_name, \
					ft_strlen(*var_names) + ft_strlen(var_iter->var_name)) == 0)
				{
					old_value = value;
					value = ft_strjoin(old_value, var_iter->value);
					free(old_value);
					break ;
				}
			}
			var_iter = var_iter->next;
		}
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
	value = iter_var(var_iter, input, sh);
	printf("%s\n", value);
	if (value)
		return (prepare_token_arr(value, sh));
	return (NULL);
}
