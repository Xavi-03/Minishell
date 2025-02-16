/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:30:35 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/16 22:32:49 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ahora el nombre esta recortado de cXrXXsX.42barcelona.com a cXrXsX
si se ejecuta en otro pc que no sea de 42 el nombre deberia salir entero
da problemas al recortar el nombre del pc y ejecutar en casa,
dejo el nombre entero */

char	*get_hostname(void)
{
	int		fd;
	int		b_read;
	char	hostname[100];
	char	*str;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (NULL);
	b_read = read(fd, hostname, 100);
	hostname[b_read] = '\0';
	str = ft_strtrim(hostname, "\n");
	return (str);
}

char	*user_finder(char *user, char *pc, t_sh *sh)
{
	char	*prompt_user;

	user = getenv("USER");
	add_galloc(user, sh);
	pc = get_hostname();
	add_galloc(pc, sh);
	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	prompt_user = userjoin(user, pc, sh);
	if (!prompt_user)
		return ("?");
	return (prompt_user);
}

char	*path_finder(t_sh *sh)
{
	char	*prompt_path;
	int		home_len;
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	prompt_path = galloc((strlen(cwd) + 1) * sizeof(char), sh);
	prompt_path = ft_substr(cwd, 0, ft_strlen(cwd));
	add_galloc(prompt_path, sh);
	if (ft_strncmp(getenv("HOME"), prompt_path, ft_strlen(getenv("HOME"))) == 0)
	{
		home_len = ft_strlen(getenv("HOME"));
		prompt_path = ft_substr(cwd, home_len - 1, \
			ft_strlen(cwd) - home_len + 1);
		prompt_path[0] = '~';
		add_galloc(prompt_path, sh);
	}
	return (prompt_path);
}

char	*prompt_finder(t_sh *sh)
{
	char	*prompt_user;
	char	*prompt_path;
	char	*prompt;

	if (!getenv("USER") || !getenv("LOGNAME") || !getenv("SESSION_MANAGER"))
	{
		sh->env = env_backup(sh);
		return ("?$\n> ");
	}
	prompt_user = user_finder(getenv("LOGNAME"), \
		getenv("SESSION_MANAGER"), sh);
	prompt_path = path_finder(sh);
	prompt = promptjoin(prompt_user, prompt_path, sh);
	return (prompt);
}
