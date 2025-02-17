/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:20:12 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/16 23:56:00 by pohernan         ###   ########.fr       */
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
void	sigquit_handler(int signal)
{
	if (signal == SIGINT)
  		printf("\nIntercepted SIGINT!\n");
}

void	sigabrt_handler(int signal)
{
	if (signal == SIGABRT)
		printf("Quit (core dumped)\n");
}


void	subprocess_executer(t_sh *sh)
{
//	struct sigaction act;
//	bzero(&act, sizeof(act));
//	act.sa_handler = &sigquit_handler;
//	sigaction(SIGINT, &act, 0);
	prepare_file(sh);
	prepare_pipe(sh);
	//if (sh->cmd_list->redir_list->infile)
	//in_file(sh);
	//if (sh->cmd_list->redir_list->outfile)
	//out_file(sh);
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
		if (WIFSIGNALED(sh->last_command))
			sh->last_command = 128 + WTERMSIG(sh->last_command);
		else if (WIFEXITED(sh->last_command))
			sh->last_command = WEXITSTATUS(sh->last_command);
		if (temp_cmd->not_found)
			sh->last_command = 127;
		/*if (sh->last_command == 2)
			sh->last_command = 130;*/
		temp_cmd = temp_cmd->next;
	}
}

void	execute(t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	increase_shlvl(sh->env);
	execve(cmd->cmd_arr[0], cmd->cmd_arr, sh->env);
	ft_putstr_fd("minishell: Command not Found\n", 2);
	terminate(1, sh);
}
