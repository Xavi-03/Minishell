/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:19:24 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:24 by pohernan         ###   ########.fr       */
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
	char	*temp_var;
	char	temp_char[2];
	int		i;

	i = 0;
	temp = NULL;
	if (sh->cmd_list->cmd_count == 1)
	{
		print_export(sh);
		return ;
	}
	while (sh->cmd_list->cmd_arr[++i])
	{
		if (!ft_strchr(sh->cmd_list->cmd_arr[i], '='))
			temp = get_value(sh->var_list, sh->cmd_list->cmd_arr[i], sh);
		if (temp && !*temp && !ft_strchr(sh->cmd_list->cmd_arr[i], '='))
			continue ;
		if (temp && *temp)
		{
			temp = ft_strjoin("=", temp);
			add_galloc(temp, 1, sh);
			sh->cmd_list->cmd_arr[1] = \
				ft_strjoin(sh->cmd_list->cmd_arr[i], temp);
			add_galloc(sh->cmd_list->cmd_arr[1], 0, sh);
		}
		else if (sh->cmd_list->cmd_arr[i][ft_strlen(sh->cmd_list->cmd_arr[i]) - 1] == '\"'
			|| sh->cmd_list->cmd_arr[i][ft_strlen(sh->cmd_list->cmd_arr[i]) - 1] == '\'')
		{
			temp_var = ft_strchr(sh->cmd_list->cmd_arr[i], '=');
			temp_var++;
			temp = ft_strdup(temp_var);
			add_galloc(temp, 1, sh);
			*temp_var = '\0';
			temp_char[0] = *temp;
			temp_char[1] = '\0';
			temp = ft_strtrim(temp, temp_char);
			add_galloc(temp, 1, sh);
			sh->cmd_list->cmd_arr[1] = ft_strjoin(sh->cmd_list->cmd_arr[i], temp);
			add_galloc(sh->cmd_list->cmd_arr[1], 0, sh);
		}
		sh->env = add_var_env(sh);
	}
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
