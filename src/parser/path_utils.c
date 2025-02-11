/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 18:49:38 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/11 19:16:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_curr_dir(void)
{
	char	cwd[4096];
	char	*path;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	path = ft_strjoin(cwd, "/");
	if (!path)
		return (NULL);
	return (path);
}

static char	*pathfinder(char **paths, char *command)
{
	char	*filepath;
	char	*path;
	char	*cwd_command;
	char	*cwd;

	cwd = get_curr_dir();
	cwd_command = ft_strjoin(cwd, command);
	free(cwd);
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

char	*get_path(char *command)
{
	char	*env_path;
	char	**paths;
	char	*path;

	env_path = getenv("PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	path = pathfinder(paths, command);
	free_str_arr(paths);
	return (path);
}
/*
char	**create_cmd_arr(char *str, char **env)
{
	char	**cmd_arr;
	char	*path;

	if (!str || !*str)
		return (NULL);
	cmd_arr = ft_split(str, ' ');
	if (!cmd_arr)
		return (NULL);
	if (access(cmd_arr[0], X_OK) == 0)
		return (cmd_arr);
	path = get_path(cmd_arr[0]);
	if (!path)
	{
		free_str_arr(cmd_arr);
		return (NULL);
	}
	free(cmd_arr[0]);
	cmd_arr[0] = path;
	return (cmd_arr);
}
*/
