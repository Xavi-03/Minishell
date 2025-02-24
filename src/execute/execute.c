/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:20:12 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:42 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	subprocess_executer(t_sh *sh)
{
	prepare_file(1, sh);
	prepare_pipe(sh);
	prepare_file(0, sh);
	if (sh->cmd_list->built_in)
	{
		if (exec_built_in(sh))
			terminate(EXIT_FAILURE, sh);
		terminate(EXIT_SUCCESS, sh);
	}
	if (sh->cmd_list->cmd_arr)
		execute(sh);
}

void	main_process_executer(t_sh *sh)
{
	t_cmd	*temp_cmd;

	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	while (temp_cmd)
	{
		if (temp_cmd->main_process)
			sh->last_command = exec_built_in(sh);
		temp_cmd = temp_cmd->next;
	}
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	pipe_cleaner(sh);
	temp_cmd = sh->cmd_list->start;
	while (temp_cmd)
	{
		waitpid(temp_cmd->pid, &sh->last_command, 0);
		if (WIFSIGNALED(sh->last_command) && !temp_cmd->built_in)
			sh->last_command = 128 + WTERMSIG(sh->last_command);
		else if (WIFEXITED(sh->last_command) && !temp_cmd->built_in)
			sh->last_command = WEXITSTATUS(sh->last_command);
		if (temp_cmd->not_found)
			sh->last_command = 127;
		temp_cmd = temp_cmd->next;
	}
}

void	execute(t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	increase_shlvl(sh->env, sh);
	execve(cmd->cmd_arr[0], cmd->cmd_arr, sh->env);
	ft_putstr_fd("minishell: Command not Found\n", 2);
	terminate(1, sh);
}
