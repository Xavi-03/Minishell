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
