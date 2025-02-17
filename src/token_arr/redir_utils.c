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
	redir_node = galloc(sizeof(t_redir), sh);
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
