#include "../../includes/minishell.h"

char	**add_var_env(t_sh *sh)
{
	char	**new_arr;
	int		i;

	i = -1;
	while (sh->env[++i])
		;
	new_arr = galloc((i + 2) * sizeof(char *), sh);
	i = -1;
	while (sh->env[++i])
	{
		new_arr[i]= ft_strdup(sh->env[i]);
		add_galloc(new_arr[i], sh);
	}
	new_arr[i] = ft_strdup(sh->cmd_list->cmd_arr[1]); // maybe necesita cambiarse por ftstrjoin
	add_galloc(new_arr[i], sh);
	new_arr[++i] = NULL;
	return (new_arr);
}

//temp static
static int	var_in_env(char *var_name, t_sh *sh)
{
	int	flag_var;
	int	env_len;

	env_len = -1;
	flag_var = 0;
	while (sh->env[++env_len])
	{
		if (ft_strncmp(var_name, sh->env[env_len], ft_strlen(var_name)) == 0)
			flag_var = 1;
	}
	if (!flag_var)
		return (0);
	return (env_len);
}

char	**remove_var_env(char *var_name, t_sh *sh)
{
	char	**new_env;
	int	env_len;
	int	i;
	int j;

	env_len = var_in_env(var_name, sh);
	if (!env_len)
		return (NULL);
	new_env = galloc(env_len * sizeof(char *), sh);
	i = -1;
	j = -1;
	while (sh->env[++i])
	{
		if (ft_strncmp(var_name, sh->env[i], ft_strlen(var_name)) == 0)
			continue ;
		new_env[++j] = ft_strdup(sh->env[i]);
		add_galloc(new_env[j], sh);
	}
	new_env[++j] = NULL;
	return (new_env);
}
