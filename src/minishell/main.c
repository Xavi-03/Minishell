/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:24:50 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:53 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global = 1;
	}
	if (SIGQUIT == signum)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

t_sh	*init_sh(char **env)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->env = NULL;
	sh->l_galloc = NULL;
	sh->exit_value = 0;
	sh->last_command = 0;
	sh->var_list = NULL;
	sh->cmd_list = NULL;
	sh->token_arr = NULL;
	sh->syntax_error = false;
	init_galloc(sh);
	sh->var_list = var_init(sh->var_list, sh);
	if (!*env)
		sh->env = env_backup(sh);
	else
		sh->env = env;
	return (sh);
}

void	prompt_main(t_sh *sh)
{
	char	*prompt;
	char	*input;

	while (true)
	{
		prompt = prompt_finder(sh);
		input = readline(prompt);
		if (!input)
			terminate(EXIT_SUCCESS, sh);
		else
			add_history(input);
		add_galloc(input, 1, sh);
		if (g_global)
		{
			sh->last_command = 130;
			g_global = 0;
		}
		sh->line = input;
		if (input[0] != '\0')
		{
			sh->token_arr = prepare_token_arr(input, sh);
			parser(sh);
		}
		free_galloc(1, sh);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_sh		*sh;
	char		*input;

	sh = init_sh(env);
	g_global = 0;
	if (argc != 1)
	{
		input = arr_to_str(&argv[1], sh);
		sh->line = input;
		sh->token_arr = prepare_token_arr(input, sh);
		parser(sh);
		terminate(EXIT_SUCCESS, sh);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	prompt_main(sh);
	terminate (EXIT_SUCCESS, sh);
}
