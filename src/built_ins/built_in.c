#include "../../includes/minishell.h"

//void	echo_built_int()

int	is_built_in(char *input, char *cmd)
{
	if (ft_strncmp(input, cmd, ft_strlen(input)) == 0)
		return (1);
	return (0);
}

void	set_main_process(t_sh *sh)
{
	sh->cmd_list->main_process = 1;
}

void	find_built_in(char *input, t_sh *sh)
{
	if (is_built_in(input, "echo"))
		;
	else if (is_built_in(input, "cd"))
		set_main_process(sh);
	else if (is_built_in(input, "pwd"))
		;
	else if (is_built_in(input, "export"))
		set_main_process(sh);
	else if (is_built_in(input, "unset"))
		set_main_process(sh);
	else if (is_built_in(input, "env"))
		set_main_process(sh);
	else if (is_built_in(input, "exit"))
		set_main_process(sh);
	else
		return ;
	sh->cmd_list->built_in = 1;
}

int	exec_built_in(t_sh *sh)
{
	char	*cmd;

	cmd = sh->cmd_list->cmd_arr[0];
	if (is_built_in(cmd, "echo"))
		echo(sh);
	else if (is_built_in(cmd, "cd"))
		cd(sh);
	else if (is_built_in(cmd, "pwd"))
		printf("pwd\n");
	else if (is_built_in(cmd, "export"))
		export(sh);
	else if (is_built_in(cmd, "unset"))
		unset(sh);
	else if (is_built_in(cmd, "env"))
		print_env(sh);
	else if (is_built_in(cmd, "exit"))
		terminate(sh); // exit en terminate
	else
		return (1);
	return (0);
}

void	cd(t_sh *sh)
{
	char	*home_path;
	char	*path;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	home_path = getenv("HOME");
	if (cmd->cmd_count == 1)
	{
		chdir(home_path);
		return ;
	}
	path = cmd->cmd_arr[1];
	if (path[0] == '~')
	{
		if (ft_strlen(path) > 1)
			home_path = ft_strjoin(home_path, path + 1);
		else
			home_path = ft_strdup(home_path);
		chdir(home_path);
		free(home_path);
	}
	chdir(path);
}

void	echo(t_sh *sh)
{
	int		i;
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	i = 0;
	if (cmd->cmd_count == 1)
		printf("\n");
	if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) == 0)
		i++;
	i++;
	while (cmd->cmd_arr[i])
	{
		printf("%s", cmd->cmd_arr[i++]);
		if (cmd->cmd_arr[i])
			printf(" ");
	}
	if (ft_strncmp(cmd->cmd_arr[1], "-n", 3) != 0)
		printf("\n");
	exit (0);
}

void	print_env(t_sh *sh)
{
	int	i;
	i = -1;
	while (sh->env[++i])
		printf("%s\n", sh->env[i]);
}

void	export(t_sh *sh)
{
	char	**env_ptr;

	env_ptr = sh->env;
	//si no comprobamos que cmd_arr[1] es true da segfault al intentar strchr la magia de &&
	if (sh->cmd_list->cmd_arr[1] && !ft_strchr(sh->cmd_list->cmd_arr[1], '='))
		return ;
	if (sh->cmd_list->cmd_arr[1])
	{
		sh->env = add_var_env(sh);
	}
	else
	{
		while (*env_ptr)
			printf("%s" RESET_COLOR "\n", *env_ptr++);
	}
	/*int	i = -1;  //debug
	while (sh->env[++i]) //debug
		printf("%s\n", sh->env[i]);*/ //debug
}


void	unset(t_sh *sh)
{
	char **new_env;
	char *var_name;

	var_name = sh->cmd_list->cmd_arr[1];
	if (!var_name)
		return ;
	new_env = remove_var_env(var_name, sh);
	if (new_env)
		sh->env = new_env;
	var_delnode(var_name, sh);
}
