/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_backup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:41:48 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:32 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *env_var, t_sh *sh)
{
	int		i;
	char	**env;
	char	*value;

	env = sh->env;
	i = -1;
	if (!env)
		return (NULL);
	while (env[++i])
	{
		if (ft_strncmp(env_var, env[i], ft_strlen(env_var)) == 0)
		{
			value = ft_strdup(ft_strchr(env[i], '='));
			add_galloc(value, 0, sh);
			value++;
			return (value);
		}
	}
	return (NULL);
}

char	**env_backup(t_sh *sh)
{
	char	**env;
	char	*pwd;

	env = galloc(4 * sizeof(char *), 0, sh);
	pwd = get_curr_dir(sh);
	env[0] = ft_strjoin("PWD=", pwd);
	add_galloc(env[0], 0, sh);
	env[1] = ft_strdup("SHLVL=1");
	add_galloc(env[1], 0, sh);
	env[2] = ft_strdup("_=/usr/bin/env");
	add_galloc(env[2], 0, sh);
	env[3] = NULL;
	return (env);
}
