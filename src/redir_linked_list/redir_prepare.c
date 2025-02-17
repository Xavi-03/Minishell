#include "../../includes/minishell.h"

static void	prepare_in_file(t_redir *redir, int flag, t_sh *sh)
{
	if (flag)
	{
		if (redir->fd_in_red)
			heredoc(redir, sh);
		if (redir->infile && !redir->fd_in_red)
			redir->fd_in = open(redir->infile, O_RDONLY);
		if (redir->fd_in < 0 && redir->infile)
		{
			ft_putstr_fd("infile error\n", 2);
			exit(1);
		}
		return ;
	}
	if (redir->infile)
	{
		if (redir->next && redir->next->infile)
			dup2(redir->next->fd_in, redir->fd_in);
		else
			dup2(redir->fd_in, STDIN_FILENO);
		close(redir->fd_in);
	}
}

static void	prepare_out_file(t_redir *redir, int flag)
{
	if (flag)
	{
		if (redir->fd_out_red)
			redir->fd_out = open(redir->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->outfile)
			redir->fd_out = open(redir->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redir->fd_out < 0 && redir->outfile)
		{
			ft_putstr_fd("outfile error\n", 2);
			exit(1);
		}
		return ;
	}
	if (redir->outfile)
	{
		if (redir->next && redir->next->outfile)
			dup2(redir->next->fd_out, redir->fd_out);
		else
			dup2(redir->fd_out, STDOUT_FILENO);
		close(redir->fd_out);
	}
}

void	prepare_file(int flag, t_sh *sh)
{
	t_redir	*redir;

	redir = sh->cmd_list->redir_list;
	redir = redir->start;
	if (!redir->infile && !redir->outfile)
		return ;
	while (redir)
	{
		prepare_in_file(redir, flag, sh);
		prepare_out_file(redir, flag);
		redir = redir->next;
	}
}
