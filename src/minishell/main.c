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

//Aqui hago malloc porque estoy guardando con add_galloc en find_cmd
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

int	main(int argc, char **argv, char **env)
{
	char		*input;
	char		*prompt;
	t_sh		*sh;
	(void)argv; // TODO: Handle argv

	sh = malloc(sizeof(t_sh));
	sh->l_galloc = NULL;
	sh->env = env;
	sh->last_command = 0;
	sh->var_list = var_init(sh->var_list, sh);
	sh->cmd_list = NULL;
	sh->input_arr = NULL;
	if (argc != 1)
	{
		//parser(arr_copy(&argv[1]), sh);
		terminate (sh);
		exit(EXIT_FAILURE);// implement execute the input(**argv) and exit
	}

	signal(SIGINT, sig_handler);
	while (true)
	{
		if (!env)
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
	terminate (sh);
	return (0);
}
