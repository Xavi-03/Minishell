/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:47:47 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:37:50 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*redir_addnode(t_sh *sh)
{
	t_redir	*new_node;

	new_node = NULL;
	new_node = redir_init(new_node, sh);
	new_node->start = sh->cmd_list->redir_list->start;
	sh->cmd_list->redir_list->next = new_node;
	sh->cmd_list->redir_list = new_node;
	return (new_node);
}

t_redir	*redir_init(t_redir *redir_node, t_sh *sh)
{
	redir_node = galloc(sizeof(t_redir), 1, sh);
	redir_node->f_next_infile = 0;
	redir_node->fd_in = 0;
	redir_node->fd_in_red = 0;
	redir_node->pipe_fd = NULL;
	redir_node->pid = 42;
	redir_node->infile = NULL;
	redir_node->f_next_outfile = 0;
	redir_node->fd_out = 0;
	redir_node->fd_out_red = 0;
	redir_node->outfile = NULL;
	redir_node->next = NULL;
	redir_node->start = NULL;
	return (redir_node);
}

int	check_redirs(t_sh *sh)
{
	t_redir	*redir;
	int		pid;

	redir = sh->cmd_list->redir_list;
	if (!redir->infile && !redir->outfile)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Fork Error\n", 2);
		terminate(EXIT_FAILURE, sh);
	}
	if (pid == 0)
	{
		prepare_file(1, sh);
		prepare_file(0, sh);
		terminate(0, sh);
	}
	waitpid(pid, &sh->last_command, 0);
	if (WIFSIGNALED(sh->last_command))
		sh->last_command = 128 + WTERMSIG(sh->last_command);
	else if (WIFEXITED(sh->last_command))
		sh->last_command = WEXITSTATUS(sh->last_command);
	return (0);
}
