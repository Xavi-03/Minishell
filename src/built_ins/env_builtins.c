/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:19:24 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/13 22:59:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_sh *sh)
{
	char	**env_ptr;

	if (!sh->env)
		return ;
	env_ptr = sh->env;
	while (*env_ptr)
		printf("%s\n", *env_ptr++);
}

void	print_export(t_sh *sh)
{
	char	**env_ptr;
	char	*eq_ptr;
	char	**var_ptr;
	char	**var;

	env_ptr = sh->env;
	while (*env_ptr)
	{
		eq_ptr = ft_strchr((const char *)*env_ptr, '=');
		if (!eq_ptr)
			return ;
		var = ft_split((const char *)*env_ptr, '=');
		printf("declare -x %s=\"%s\"\n", var[0], var[1]);
		var_ptr = var;
		while (*var)
			free(*var++);
		free(var_ptr);
		env_ptr++;
	}
}

void	export(t_sh *sh)
{
	char	*temp;

	if (sh->cmd_list->cmd_arr[1])
	{
		temp = get_value(sh->var_list, sh->cmd_list->cmd_arr[1], sh);
		if (temp)
		{
			temp = ft_strjoin("=", temp);
			add_galloc(temp, sh);
			sh->cmd_list->cmd_arr[1] = \
				ft_strjoin(sh->cmd_list->cmd_arr[1], temp);
			add_galloc(sh->cmd_list->cmd_arr[1], sh);
		}
	}
	if (sh->cmd_list->cmd_arr[1] && !ft_strchr(sh->cmd_list->cmd_arr[1], '='))
		return ;
	if (sh->cmd_list->cmd_arr[1])
		sh->env = add_var_env(sh);
	else
		print_export(sh);
}

void	unset(t_sh *sh)
{
	char	**new_env;
	char	*var_name;

	var_name = sh->cmd_list->cmd_arr[1];
	if (!var_name)
		return ;
	new_env = remove_var_env(var_name, sh);
	sh->env = new_env;
	var_delnode(var_name, sh);
}
