#include "../../includes/minishell.h"


/*void	here_doc(t_sh *sh)
{
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
}*/

// last here doc
/*if (sh->cmd_list->fd_in_red)
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
		return ;
	}*/


/*
static void	here_doc_pipe(t_redir *redir, t_sh *sh)
{
	(void)redir;
	(void)sh;
	int	temp_pipe_fd[2];

	if (pipe(temp_pipe_fd) < 0)
	{
		ft_putstr_fd("Pipe Error\n", 2);
		terminate(EXIT_FAILURE, sh);
	}
	redir->pipe_fd = galloc(2 * sizeof(int), sh);
	redir->pipe_fd[0] = temp_pipe_fd[0];
	redir->pipe_fd[1] = temp_pipe_fd[1];
	dup2(redir->fd_in, redir->pipe_fd[1]);
	//dup2(redir->pipe_fd[0], redir->fd_in);
	dup2(redir->pipe_fd[1], redir->fd_in);
	close(redir->pipe_fd[0]);
	close(redir->pipe_fd[1]);
}

static void	here_doc(t_redir *redir, t_sh *sh)
{
	char	*arr[100];
	int	i;

	printf("in %i  out %i\n", redir->pipe_fd[0], redir->pipe_fd[1]);
	redir->pid = fork();
	if (redir->pid < 0)
	{
		ft_putstr_fd("Fork Error\n", 2);
		terminate(EXIT_FAILURE, sh);
	}
	else if (redir->pid > 0)
	{
		if (!redir->next)
		{
			write(2, "__\n", 3);
			dup2(redir->pipe_fd[0], STDIN_FILENO);
		}
		close(redir->pipe_fd[0]);
		close(redir->pipe_fd[1]);
		waitpid(redir->pid, NULL, 0);
		return ;
	}
	if (!redir->next)
	{
		write(2, "..\n", 3);
		dup2(redir->pipe_fd[1], STDOUT_FILENO);
	}
	//close(redir->pipe_fd[1]);
	//close(redir->pipe_fd[0]);
	i = 0;
	while (true)
	{
		arr[i] = get_next_line(0);
		add_galloc(arr[i], sh);
		if (ft_strncmp(arr[i], redir->infile, ft_strlen(redir->infile)) == 0)
		{
			arr[i] = NULL;
			break ;
		}
		i++;
	}
	i = -1;
	while (arr[++i] && !redir->next)
		printf("%s", arr[i]);
	redir = redir->start;
	while (redir)
	{
		if (redir->fd_in_red)
		{
			close(redir->pipe_fd[0]);
			close(redir->pipe_fd[1]);
		}
		redir = redir->next;
	}
	terminate(0, sh);
}
*/

static void	prepare_in_file(t_redir *redir, int flag, t_sh *sh)
{
	if (flag)
	{
		if (redir->fd_in_red)
		{//TODO: here_doc
			heredoc(redir, sh);
		}
		if (redir->infile && !redir->fd_in_red)
			redir->fd_in = open(redir->infile, O_RDONLY);
		if (redir->fd_in < 0 && redir->infile)
		{
			printf("infile error\n");
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
			printf("outfile error\n");
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
	{
		printf("1\n");
		return ;
	}
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
