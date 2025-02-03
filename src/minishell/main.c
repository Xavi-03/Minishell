/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:24:50 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/04 00:39:05 by pohernan         ###   ########.fr       */
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
	}
}

/* Aqui hago malloc porque estoy guardando con add_galloc en find_cmd */
char	**arr_copy(char **arr)
{
	int		i;
	char	**new_arr;

	i = -1;
	while (arr[++i])
		;
	new_arr = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (arr[++i])
		new_arr[i] = ft_strdup(arr[i]);
	new_arr[i] = NULL;
	return (new_arr);
}

t_sh	*init_sh(char **env)
{
	t_sh	*sh;

	sh = malloc(sizeof(t_sh));
	if (!sh)
		return (NULL);
	sh->l_galloc = NULL;
	sh->env = env;
	sh->last_command = 0;
	sh->var_list = var_init(sh->var_list, sh);
	sh->cmd_list = NULL;
	sh->input_arr = NULL;
	return (sh);
}

void	prompt_main(t_sh *sh)
{
	char	*prompt;
	char	*input;

	while (true)
	{
		if (!sh->env)
			prompt = "minishell> ";
		else
			prompt = prompt_finder(sh);
		input = readline(prompt);
		if (!input)
			terminate(sh);
		else
			add_history(input);
		add_galloc(input, sh);
		sh->line = input;
		if (input[0] != '\0')
		{
			sh->input_arr = prepare_cmd_arr(input);
			parser(sh);
		}
		gfree(input, sh);
	}
}

/* TODO: Handle argv */
int	main(int argc, char **argv, char **env)
{
	t_sh		*sh;

	(void)argv;
	sh = init_sh(env);
	if (argc != 1)
	{
		terminate (sh);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	prompt_main(sh);
	terminate (sh);
	return (0);
}
