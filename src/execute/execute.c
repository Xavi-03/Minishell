#include "../../includes/minishell.h"

void	in_file(t_sh *sh)
{
	if (sh->cmd_list->fd_in_red)
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	else
		sh->cmd_list->fd_in = open(sh->cmd_list->infile, O_RDONLY);
	if (sh->cmd_list->fd_in < 0)
	{
		printf("infile error\n");
		exit(1);
	}
	dup2(sh->cmd_list->fd_in, STDIN_FILENO);
	close(sh->cmd_list->fd_in);
}

void	out_file(t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (cmd->fd_out_red)
		cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
	{
		printf("outfile error\n");
		exit(1);
	}
	dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->fd_out);
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

void	execute(t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	execve(cmd->cmd_arr[0], cmd->cmd_arr, sh->env);
	printf("minishell: Command not Found %s\n", cmd->cmd_arr[0]);
	exit (1);
}
