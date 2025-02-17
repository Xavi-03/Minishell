/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:40:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:42:10 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	increase_shlvl(char **env)
{
	char	*sh_lvl;

	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 6) == 0 \
			&& ft_strlen(*env) > 6)
		{
			sh_lvl = ft_itoa(ft_atoi(*env + 6) + 1);
			*env = ft_strjoin("SHLVL=", sh_lvl);
			free(sh_lvl);
		}
		env++;
	}
}
