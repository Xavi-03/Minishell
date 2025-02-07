/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:19:24 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/04 00:19:37 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_sh *sh)
{
	char	**env_ptr;

	env_ptr = sh->env;
	while (*env_ptr)
		printf("%s" RESET_COLOR "\n", *env_ptr++);
}

void	export(t_sh *sh)
{
	if (sh->cmd_list->cmd_arr[1] && !ft_strchr(sh->cmd_list->cmd_arr[1], '='))
		return ;
	if (sh->cmd_list->cmd_arr[1])
	{
		sh->env = add_var_env(sh);
	}
	else
		print_env(sh);
}

void	unset(t_sh *sh)
{
	char	**new_env;
	char	*var_name;

	var_name = sh->cmd_list->cmd_arr[1];
	if (!var_name)
		return ;
	new_env = remove_var_env(var_name, sh);
	if (new_env)
		sh->env = new_env;
	var_delnode(var_name, sh);
}
