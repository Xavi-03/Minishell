#include "../../includes/minishell.h"


void	here_doc(t_sh *sh)
{
	//char	*line;
	int		i;
	char	*arr[100];

	i = 0;
	dup2(sh->cmd_list->fd_pipe[1], STDOUT_FILENO);
	close(sh->cmd_list->fd_pipe[0]);
	close(sh->cmd_list->fd_pipe[1]);
	while (true)
	{
		write(1, "> ", 2);
		arr[i] = get_next_line(0);
		add_galloc(arr[i], sh);
		if (ft_strncmp(arr[i], sh->cmd_list->infile, ft_strlen(sh->cmd_list->infile)) == 0)
		{
			arr[i] = NULL;
			break ;
		}
		i++;
	}
	i = -1;
	while (arr[++i])
		printf("%s", arr[i]);
	terminate(0, sh);
}

void	in_file(t_sh *sh)
{
	int		fd_pipe[2];

	if (sh->cmd_list->fd_in_red)
	{
		sh->cmd_list->fd_pipe = galloc(2 * sizeof(int *), sh);
		if (pipe(fd_pipe) < 0)
		{
			ft_putstr_fd("Pipe Error\n", 2);
			terminate(EXIT_FAILURE, sh);
		}
		sh->cmd_list->fd_pipe[0] = fd_pipe[0];
		sh->cmd_list->fd_pipe[1] = fd_pipe[1];
		sh->cmd_list->pid = fork();
		if (sh->cmd_list->pid == -1)
		{
			ft_putstr_fd("Fork Error\n", 2);
			terminate(EXIT_FAILURE, sh);
		}
		if (sh->cmd_list->pid == 0)
		{
			here_doc(sh);
			terminate(0, sh);
		}
		dup2(sh->cmd_list->fd_pipe[0], STDIN_FILENO);
		close(sh->cmd_list->fd_pipe[0]);
		close(sh->cmd_list->fd_pipe[1]);
	}
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
