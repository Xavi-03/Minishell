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
		{
			if (!redir->fd_in_red)
				dup2(redir->next->fd_in, redir->fd_in);
		}
		else
		{
			if (!redir->fd_in_red)
				dup2(redir->fd_in, STDIN_FILENO);
		}
		if (!redir->fd_in_red)
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

void	prepare_file(t_sh *sh)
{
	t_redir	*redir;

	redir = sh->cmd_list->redir_list;
	redir = redir->start;
	if (!redir->infile && !redir->outfile)
		return ;
	while (redir)
	{
		prepare_in_file(redir, 1, sh);
		prepare_out_file(redir, 1);
		redir = redir->next;
	}
	redir = sh->cmd_list->redir_list->start;
	while (redir)
	{
		prepare_in_file(redir, 0, sh);
		prepare_out_file(redir, 0);
		redir = redir->next;
	}
}

t_cmd	*fork_create(t_sh *sh)
{
	t_cmd	*cmd_node;

	sh->cmd_list = sh->cmd_list->start;
	cmd_node = sh->cmd_list->start;
	while (cmd_node)
	{
		if (!cmd_node->main_process)
		{
			cmd_node->pid = fork();
			if (!cmd_node->pid)
				return (cmd_node);
			if (!cmd_node->cmd_arr[0])
				cmd_node->not_found = 1;
		}
		cmd_node = cmd_node->next;
	}
	return (sh->cmd_list);
}

void	prepare_pipe(t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (cmd->in_pipe)
		dup2(cmd->fd_pipe[0], STDIN_FILENO);
	if (cmd->out_pipe)
		dup2(cmd->next->fd_pipe[1], STDOUT_FILENO);
	pipe_cleaner(sh);
}

void	pipe_cleaner(t_sh *sh)
{
	t_cmd	*cmd_node;

	cmd_node = sh->cmd_list->start;
	while (cmd_node)
	{
		if (cmd_node->fd_pipe)
		{
			close(cmd_node->fd_pipe[0]);
			close(cmd_node->fd_pipe[1]);
		}
		cmd_node = cmd_node->next;
	}
}
