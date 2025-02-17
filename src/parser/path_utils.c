/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:49:38 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/15 17:44:56 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_curr_dir(t_sh *sh)
{
	char	cwd[4096];
	char	*path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	if (ft_strlen(cwd) == 1 && *cwd == '/')
		path = ft_strdup(cwd);
	else
		path = ft_strjoin(cwd, "/");
	add_galloc(path, sh);
	if (!path)
		return (NULL);
	return (path);
}

static char	*pathfinder(char **paths, char *command, t_sh *sh)
{
	char	*filepath;
	char	*path;
	char	*cwd_command;
	char	*cwd;

	cwd = get_curr_dir(sh);
	cwd_command = ft_strjoin(cwd, command);
	if (!cwd_command)
		return (NULL);
	if (access(cwd_command, X_OK) == 0)
		return (cwd_command);
	free(cwd_command);
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		filepath = ft_strjoin(path, command);
		free(path);
		if (access(filepath, X_OK) == 0)
			return (filepath);
		free(filepath);
		paths++;
	}
	return (NULL);
}

char	*get_path(char *command, t_sh *sh)
{
	char	*env_path;
	char	**paths;
	char	*path;

	env_path = ft_get_env("PATH", sh);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	path = pathfinder(paths, command, sh);
	free_str_arr(paths);
	return (path);
}
