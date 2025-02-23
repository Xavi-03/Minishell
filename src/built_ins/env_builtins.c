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

static void	export_extend_one(char *temp_val, int i, t_sh *sh)
{
	char	**cmd_arr;

	cmd_arr = sh->cmd_list->cmd_arr;
	temp_val = ft_strjoin("=", temp_val);
	add_galloc(temp_val, 1, sh);
	cmd_arr[i] = ft_strjoin(cmd_arr[i], temp_val);
	add_galloc(cmd_arr[i], 0, sh);
}

static void	export_extend_two(char *temp_val, \
	char *temp_var_name, int i, t_sh *sh)
{
	char	**cmd_arr;

	cmd_arr = sh->cmd_list->cmd_arr;
	temp_var_name = ft_strchr(cmd_arr[i], '=');
	temp_var_name++;
	temp_val = ft_strdup(temp_var_name);
	add_galloc(temp_val, 1, sh);
	*temp_var_name = '\0';
	if (extract_between_chars(temp_val, '\"', sh))
		temp_val = extract_between_chars(temp_val, '\"', sh);
	else
		temp_val = extract_between_chars(temp_val, '\'', sh);
	cmd_arr[i] = ft_strjoin(cmd_arr[i], temp_val);
	add_galloc(cmd_arr[i], 0, sh);
}

void	export(t_sh *sh)
{
	char	*temp_val;
	char	*temp_var_name;
	char	**cmd_arr;
	int		i;

	temp_var_name = NULL;
	i = 0;
	cmd_arr = sh->cmd_list->cmd_arr;
	if (sh->cmd_list->cmd_count == 1)
		print_export(sh);
	while (cmd_arr[++i])
	{
		temp_val = NULL;
		if (!ft_strchr(cmd_arr[i], '='))
			temp_val = get_value(sh->var_list, cmd_arr[i], sh);
		if (temp_val && !*temp_val && !ft_strchr(cmd_arr[i], '='))
			continue ;
		if (temp_val && *temp_val)
			export_extend_one(temp_val, i, sh);
		else if (cmd_arr[i][ft_strlen(cmd_arr[i]) - 1] == '\"'
			|| cmd_arr[i][ft_strlen(cmd_arr[i]) - 1] == '\'')
			export_extend_two(temp_val, temp_var_name, i, sh);
		cmd_arr[1] = cmd_arr[i];
		sh->env = add_var_env(sh);
	}
}

void	unset(t_sh *sh)
{
	char	**new_env;
	char	**cmd_arr;
	int		i;

	i = 0;
	cmd_arr = sh->cmd_list->cmd_arr;
	while (cmd_arr[++i])
	{
		if (!cmd_arr[i])
			break ;
		new_env = remove_var_env(cmd_arr[i], sh);
		if (new_env)
			sh->env = new_env;
		var_delnode(cmd_arr[i], sh);
	}
}
