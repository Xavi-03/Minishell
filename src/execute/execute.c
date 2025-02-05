/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:20:12 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/04 00:20:13 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigler(int signum)
{
	(void)signum;
	/*if (signum == SIGINT)
	{
		printf("Hola\n");
		exit(42);
	}*/
}

void	subprocess_executer(t_sh *sh)
{
	prepare_pipe(sh);
	if (sh->cmd_list->infile)
		in_file(sh);
	if (sh->cmd_list->outfile)
		out_file(sh);
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
			exec_built_in(sh);
		temp_cmd = temp_cmd->next;
	}
	sh->cmd_list = sh->cmd_list->start;
	temp_cmd = sh->cmd_list;
	pipe_cleaner(sh);
	temp_cmd = sh->cmd_list->start;
	while (temp_cmd)
	{
		waitpid(temp_cmd->pid, &sh->last_command, 0);
		//if (sh->last_command == 256)
		//	sh->last_command -= 129;
		temp_cmd = temp_cmd->next;
	}
}

void	execute(t_sh *sh)
{
	t_cmd	*cmd;
	/*char **str = galloc(2 * sizeof(char *), sh);
	str[0] = "./bat";
	str[1] = NULL;*/

	cmd = sh->cmd_list;
	execve(cmd->cmd_arr[0], cmd->cmd_arr, sh->env);
	//printf("%i\n", execve(str[0], str, sh->env));
	printf("minishell: Command not Found\n");
	terminate(1, sh);
}
