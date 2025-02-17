/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:18:02 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/15 16:51:26 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwd_env(t_sh *sh)
{
	char	*new_var;

	sh->cmd_list->cmd_arr = galloc(3 * sizeof(char *), sh);
	new_var = ft_strjoin("OLDPWD=", ft_get_env("PWD", sh));
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

void	cd(t_sh *sh)
{
	char	*home_path;
	char	*path;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	home_path = ft_get_env("HOME", sh);
	if (cmd->cmd_count == 1 && home_path)
	{
		chdir(home_path);
		update_pwd_env(sh);
		return ;
	}
	path = cmd->cmd_arr[1];
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
