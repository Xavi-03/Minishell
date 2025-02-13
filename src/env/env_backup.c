#include "../../includes/minishell.h"

char	*ft_get_env(char *env_var, t_sh *sh)
{
	int		i;
	char	**env;

	env = sh->env;
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env_var, env[i], ft_strlen(env_var)) == 0)
			return (add_galloc(ft_strdup(ft_strchr(env[i], '=')), sh));
	}
	return (NULL);
}

char	**env_backup(t_sh *sh)
{
	char	**env;
	char	*pwd;

	env = galloc(4 * sizeof(char *), sh);
	pwd = get_curr_dir();
	env[0] = ft_strjoin("PWD=", pwd);
	free(pwd);
	add_galloc(env[0], sh);
	env[1] = ft_strdup("SHLVL=1");
	add_galloc(env[1], sh);
	env[2] = ft_strdup("_=/usr/bin/env");
	add_galloc(env[2], sh);
	env[3] = NULL;
	return (env);
}
