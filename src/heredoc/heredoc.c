/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:44:30 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/16 19:36:33 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_redir *redir, t_sh *sh)
{
	char	*line;
	int		fd;
	char	*filename;
	char	nl;

	(void)sh;
	nl = '\n';
	filename = "/tmp/heredoc";
	remove(filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	line = readline("> ");
	add_galloc(line, sh);
	while (ft_strncmp(line, redir->infile, strlen(line)))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		line = readline("> ");
		add_galloc(line, sh);
	}
	redir->fd_in = fd;
	redir->fd_in_red = 0;
	redir->infile = ft_strdup(filename);
	close(fd);
	add_galloc(redir->infile, sh);
}

int	readline_to_filename(char *eof, t_sh *sh)
{
	char	*line;
	int		fd;
	char	*filename;
	char	nl;

	(void)sh;
	nl = '\n';
	filename = "/tmp/heredoc";
	remove(filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	line = readline("> ");
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	while (ft_strncmp(line, eof, strlen(eof)))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		line = readline("> ");
	}
	return (fd);
}

/*
int	readline_to_fd(char *heredoc, t_sh *sh)
{
	char	*line;
	char	*eof;
	int		fd;
	char	*filename;
	char	nl;

	(void)sh;
	nl = '\n';
	filename = "/tmp/heredoc";
	remove(filename);
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	eof = heredoc;
	line = readline("> ");
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	while (ft_strncmp(line, eof, strlen(eof)))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		line = readline("> ");
	}
	return (fd);
}

int	main(void)
{
	readline_to_fd("eof", NULL);
}
*/
