/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:18:02 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 23:18:45 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(t_sh *sh)
{
	char	*new_var;

	sh->cmd_list->cmd_arr = galloc(3 * sizeof(char *), sh);
	new_var = ft_get_env("PWD", sh);
	if (!new_var)
		new_var = get_curr_dir(sh);
	new_var = ft_strjoin("OLDPWD=", new_var);
	add_galloc(new_var, sh);
	sh->cmd_list->cmd_arr[0] = NULL;
	sh->cmd_list->cmd_arr[1] = ft_strdup(new_var);
	add_galloc(sh->cmd_list->cmd_arr[1], sh);
	sh->cmd_list->cmd_arr[2] = NULL;
	sh->env = add_var_env(sh);
	new_var = ft_strjoin("PWD=", get_curr_dir(sh));
	add_galloc(new_var, sh);
	sh->cmd_list->cmd_arr[0] = NULL;
	sh->cmd_list->cmd_arr[1] = ft_strdup(new_var);
	add_galloc(sh->cmd_list->cmd_arr[1], sh);
	sh->cmd_list->cmd_arr[2] = NULL;
	sh->env = add_var_env(sh);
}

static bool	cd_home(char *home_path, t_sh *sh)
{
	if (sh->cmd_list->cmd_count == 1)
	{
		if (home_path)
		{
			chdir(home_path);
			update_pwd_env(sh);
		}
		return (true);
	}
	return (false);
}

static bool	cd_olddir(char *path, t_sh *sh)
{
	char	*oldpwd;

	if (!path)
		return (false);
	if (ft_strlen(path) == 1 && *path == '-')
	{
		oldpwd = ft_get_env("OLDPWD", sh);
		if (oldpwd)
		{
			chdir(oldpwd);
			update_pwd_env(sh);
			return (true);
		}

	}
	return (false);
}

void	cd(t_sh *sh)
{
	char	*home_path;
	char	*path;

	home_path = ft_get_env("HOME", sh);
	path = sh->cmd_list->cmd_arr[1];
	if (cd_home(home_path, sh))
		return ;
	if (cd_olddir(path, sh))
		return ;
	if (path[0] == '~' && home_path)
	{
		if (ft_strlen(path) > 1)
			home_path = ft_strjoin(home_path, path + 1);
		else
			home_path = ft_strdup(home_path);
		chdir(home_path);
		free(home_path);
	}
	chdir(path);
	update_pwd_env(sh);
}

void	pwd(t_sh *sh)
{
	char	*cwd;

	cwd = get_curr_dir(sh);
	printf("%s\n", cwd);
}
