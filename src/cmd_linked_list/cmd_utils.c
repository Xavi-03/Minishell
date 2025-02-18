/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:22:06 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:27 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*cmd_addnode(t_sh *sh)
{
	t_cmd	*new_node;

	new_node = NULL;
	new_node = cmd_init(new_node, sh);
	new_node->start = sh->cmd_list->start;
	sh->cmd_list->next = new_node;
	sh->cmd_list = new_node;
	sh->cmd_list->redir_list = redir_init(sh->cmd_list->redir_list, sh);
	sh->cmd_list->redir_list->start = sh->cmd_list->redir_list;
	return (new_node);
}

t_cmd	*cmd_init(t_cmd *cmd_list, t_sh *sh)
{
	cmd_list = galloc(sizeof(t_cmd), sh);
	cmd_list->pid = 42;
	cmd_list->not_found = 0;
	cmd_list->cmd_count = 0;
	cmd_list->main_process = 0;
	cmd_list->in_pipe = 0;
	cmd_list->out_pipe = 0;
	cmd_list->fd_pipe = NULL;
	cmd_list->next = NULL;
	cmd_list->start = NULL;
	cmd_list->built_in = 0;
	cmd_list->redir_list = NULL;
	cmd_list->redir_list = redir_init(cmd_list->redir_list, sh);
	cmd_list->redir_list->start = cmd_list->redir_list;
	return (cmd_list);
}
