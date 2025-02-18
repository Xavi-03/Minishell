/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:32:30 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 23:59:47 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_prompt_val(char **prompt, char **val)
{
	ft_strlcat(*prompt, *val, ft_strlen(*prompt) + ft_strlen(*val) + 1);
}

char	*promptjoin(char *user, char *path, t_sh *sh)
{
	char	*div1;
	char	*div2;
	char	*prompt;

	if (!user)
		user = "?";
	if (!path)
		path = "?";
	div1 = ":";
	div2 = "$\n> ";
	prompt = galloc((ft_strlen(user) + ft_strlen(div1) + \
		ft_strlen(path) + ft_strlen(div2) + 1), sh);
	prompt[0] = '\0';
	join_prompt_val(&prompt, &user);
	join_prompt_val(&prompt, &div1);
	join_prompt_val(&prompt, &path);
	join_prompt_val(&prompt, &div2);
	return (prompt);
}

char	*userjoin(char *user, char *pc, t_sh *sh)
{
	char	*div1;
	char	*prompt;

	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	div1 = "@";
	prompt = galloc((ft_strlen(user) + ft_strlen(div1) + \
		ft_strlen(pc) + 1), sh);
	prompt[0] = '\0';
	join_prompt_val(&prompt, &user);
	join_prompt_val(&prompt, &div1);
	join_prompt_val(&prompt, &pc);
	return (prompt);
}
