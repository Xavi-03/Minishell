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
		;
	else if (is_built_in(input, "env"))
		;
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
		printf("unset\n");
	else if (is_built_in(cmd, "env"))
		printf("env\n");
	else if (is_built_in(cmd, "exit"))
	{
		terminate(sh);
		exit(EXIT_SUCCESS);
	}
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

void	export(t_sh *sh)
{
	char	**env_ptr;

	env_ptr = sh->env;
	while (*env_ptr)
		printf("%s" RESET_COLOR "\n", *env_ptr++);
}
