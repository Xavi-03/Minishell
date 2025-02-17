/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 23:56:01 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:41:40 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	cmp_var_names(char *first_var, char *second_var)
{
	if (ft_strncmp(first_var, second_var, ft_strlen(first_var) - \
		ft_strlen(ft_strchr(first_var, '='))) == 0)
		return (true);
	return (false);
}

static char	**dup_modify_env(t_sh *sh, char *var_str, char **new_arr)
{
	int		i;
	bool	var_exists;

	i = -1;
	var_exists = false;
	while (sh->env[++i])
	{
		if (cmp_var_names(var_str, sh->env[i]))
		{
			var_exists = true;
			new_arr[i] = ft_strdup(var_str);
		}
		else
			new_arr[i] = ft_strdup(sh->env[i]);
		add_galloc(new_arr[i], sh);
	}
	if (!var_exists)
	{
		new_arr[i] = ft_strdup(var_str);
		add_galloc(new_arr[i], sh);
	}
	new_arr[++i] = NULL;
	return (new_arr);
}

char	**add_var_env(t_sh *sh)
{
	char	**new_arr;
	int		i;
	char	*var_str;

	i = -1;
	var_str = sh->cmd_list->cmd_arr[1];
	while (sh->env[++i])
		;
	new_arr = galloc((i + 2) * sizeof(char *), sh);
	new_arr = dup_modify_env(sh, var_str, new_arr);
	return (new_arr);
}

//temp static
static int	var_in_env(char *var_name, t_sh *sh)
{
	int	flag_var;
	int	env_len;

	env_len = -1;
	flag_var = 0;
	while (sh->env[++env_len])
	{
		if (ft_strncmp(var_name, sh->env[env_len], ft_strlen(var_name)) == 0)
			flag_var = 1;
	}
	if (!flag_var)
		return (0);
	return (env_len);
}

char	**remove_var_env(char *var_name, t_sh *sh)
{
	char	**new_env;
	int		env_len;
	int		i;
	int		j;

	env_len = var_in_env(var_name, sh);
	if (!env_len || env_len == 1)
		return (NULL);
	new_env = galloc(env_len * sizeof(char *), sh);
	i = -1;
	j = -1;
	while (sh->env[++i])
	{
		if (ft_strncmp(var_name, sh->env[i], ft_strlen(var_name)) == 0)
			continue ;
		new_env[++j] = ft_strdup(sh->env[i]);
		add_galloc(new_env[j], sh);
	}
	new_env[++j] = NULL;
	return (new_env);
}
