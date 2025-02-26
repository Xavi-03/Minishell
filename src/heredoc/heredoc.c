/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:44:30 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/25 20:53:03 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_subprocess(int signum)
{
	if (signum == SIGINT)
	{
		exit (130);
		g_global = 1;
	}
	if (SIGQUIT == signum)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	heredoc(t_redir *redir, t_sh *sh)
{
	char	*line;
	int		fd;
	char	*filename;

	(void)sh;
	filename = "/tmp/heredoc";
	remove(filename);
	signal(SIGINT, sig_subprocess);
	signal(SIGQUIT, sig_subprocess);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	line = readline("> ");
	add_galloc(line, 1, sh);
	while (line && (!*line || ft_strncmp(line, redir->infile, \
		strlen(redir->infile) + 1)))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		line = readline("> ");
		add_galloc(line, 0, sh);
	}
	redir->fd_in = fd;
	redir->fd_in_red = 0;
	redir->infile = ft_strdup(filename);
	close(fd);
	add_galloc(redir->infile, 0, sh);
}
