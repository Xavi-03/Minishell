/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:24:50 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/06 19:19:48 by pohernan         ###   ########.fr       */
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
	if (SIGQUIT == signum)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Aqui hago malloc porque estoy guardando con add_galloc en find_cmd */
char	*arr_to_str(char **arr)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = 0;
	while (arr[++i])
	{
		j += ft_strlen(arr[i]);
		if (arr[i + 1])
			j += 1;
	}
	new_str = malloc((j + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	i = -1;
	j = -1;
	while (*arr)
	{
		ft_strlcat(new_str, *arr, ft_strlen(new_str) + 2 + ft_strlen(*arr));
		if (arr[1])
			ft_strlcat(new_str, " ", ft_strlen(new_str) + 2);
		arr++;
	}
	return (new_str);
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
	sh->var_list = NULL;
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
			terminate(EXIT_FAILURE, sh);
		else
			add_history(input);
		add_galloc(input, sh);
		sh->line = input;
		if (input[0] != '\0')
		{
			sh->input_arr = prepare_cmd_arr(input, sh);
			parser(sh);
		}
		gfree(input, sh);
	}
}


/* TODO: Handle argv */
int	main(int argc, char **argv, char **env)
{
	t_sh		*sh;
	char		*input;

	sh = init_sh(env);
	if (argc != 1)
	{
		input = arr_to_str(&argv[1]);
		add_galloc(input, sh);
		sh->line = input;
		sh->input_arr = prepare_cmd_arr(input, sh);
		parser(sh);
		terminate(EXIT_SUCCESS, sh);
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);

	//sigaction(SIGINT, &act, 0);
	prompt_main(sh);
	terminate (EXIT_SUCCESS, sh);
}
