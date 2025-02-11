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
	char **env;

	env = galloc(6 * sizeof(char *), sh);

	env[0] = ft_strdup("SESSION_MANAGER=local/unknow:@/tmp/.ICE-unix/3750535,unix" \
		"/unknow:/tmp/.ICE-unix/3750535");
	add_galloc(env[0], sh);
	env[1] = ft_strdup("PWD=/");//get_cwd
	add_galloc(env[1], sh);
	env[2] = ft_strdup("HOME=/home/unknow");
	add_galloc(env[2], sh);
	env[3] = ft_strdup("PATH=/.local/bin/:/bin:/usr/local/sbin:/usr/local/bin:" \
		"/usr/sbin:/usr/bin:/sbin:/bin");
	add_galloc(env[3], sh);
	env[4] = ft_strdup("USER=unknow");
	add_galloc(env[4], sh);
	env[5] = NULL;
	return (env);
}
