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
}

void	pwd(void)
{
	char	*cwd;

	cwd = get_curr_dir();
	printf("%s\n", cwd);
	free(cwd);
}
