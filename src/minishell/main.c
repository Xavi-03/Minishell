#include "../../includes/minishell.h"

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        //readline("Hello>\n");
    }
}
//Aqui hago malloc porque estoy guardano con add_galloc en find_cmd
char	**arr_copy(char **arr)
{
	int i;
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
	char		*line;
	t_sh		*sh;

	int	i = 0; // debugger
	sh = malloc(sizeof(t_sh));
	sh->l_galloc = NULL;
	sh->env = env;
	sh->last_command = 0;
	sh->var_list = var_init(sh->var_list, sh);
	sh->cmd_list = NULL;
	if (argc != 1)
	{
		///sh->cmd_list = NULL;
		parser(arr_copy(&argv[1]), sh);
		terminate (sh);
		exit(1);// implement execute the input(**argv) and exit
	}

	signal(SIGINT, sig_handler);
	while(i < 5) // tmp debugger
	{
		//sh->cmd_list = NULL;
		if (env != NULL)
			line = "minishell> ";
		else
			line = line_finder(sh);
		input = readline(line);
		if (!input)
			terminate(sh);
		else
			add_history(input);
		add_galloc(input, sh);
		sh->line = input;
		if (input[0] != '\0')
			parser(ft_split(input_cleaner(input, sh), ' '), sh);
		//free(input);
		i++; // debugger
	}
	//usleep(1000000); // debug
	printf("main\n"); // debug
	terminate (sh);
	return (0);
}
