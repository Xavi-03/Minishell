/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:24:50 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 21:23:03 by pohernan         ###   ########.fr       */
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

char	*arr_to_str(char **arr, t_sh *sh)
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
	new_str = galloc((j + 1) * sizeof(char), sh);
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
	sh->token_arr = NULL;
	sh->syntax_error = false;
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
			sh->token_arr = prepare_token_arr(input, sh);
			parser(sh);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_sh		*sh;
	char		*input;

	sh = init_sh(env);
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
