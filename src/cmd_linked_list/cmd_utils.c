#include "../../includes/minishell.h"

t_cmd	*cmd_addnode(t_sh *sh)
{
	t_cmd	*new_node;

	new_node = NULL;
	new_node = cmd_init(new_node, sh);
	new_node->start = sh->cmd_list->start;
	sh->cmd_list->next = new_node;
	sh->cmd_list = new_node;
	return (new_node);
}

t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh)
{
	cmd_list = galloc(sizeof(t_cmd), sh);
	cmd_list->pid = 42;
	cmd_list->cmd_count = 0;
	cmd_list->main_process = 0;
	cmd_list->in_pipe = 0;
	cmd_list->out_pipe = 0;
	cmd_list->fd_pipe = NULL;
	cmd_list->f_next_infile = 0;
	cmd_list->fd_in_red = 0;
	cmd_list->infile = NULL;
	cmd_list->f_next_outfile = 0;
	cmd_list->fd_out_red = 0;
	cmd_list->outfile = NULL;
	cmd_list->cmd_arr = NULL;
	cmd_list->infile = NULL;
	cmd_list->outfile = NULL;
	cmd_list->next = NULL;
	cmd_list->start = NULL;
	cmd_list->built_in = 0;
	return (cmd_list);
}
