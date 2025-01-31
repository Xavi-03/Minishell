#include "../../includes/minishell.h"



//ahora el nombre esta recortado de cXrXXsX.42barcelona.com a cXrXsX
//si se ejecuta en otro pc que no sea de 42 el nombre deberia salir entero
//da problemas al recortar el nombre del pc y ejecutar en casa, dejo eel nombre entero
char	*user_finder(char *user, char *pc, t_sh *sh)
{
	char	*line_user;

	user = ft_substr(getenv("USER"), 0, ft_strlen(getenv("USER")));
	add_galloc(user, sh);
	pc = ft_strchr(getenv("SESSION_MANAGER"), '/');
	pc++;
	pc = ft_substr(pc, 0, ft_lentoc(pc, ':'));
	add_galloc(pc, sh);
	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	line_user = userjoin(user, pc, sh);
	if (!line_user)
		return ("?");
	return (line_user);
}

char	*path_finder(t_sh *sh)
{
	char	*line_path;
	int		home_len;
	char	cwd[4096];

	getcwd(cwd, sizeof(cwd));
	line_path = galloc((strlen(cwd) + 1) * sizeof(char), sh);
	line_path = ft_substr(cwd, 0, ft_strlen(cwd));
	add_galloc(line_path, sh);

	if (ft_strncmp(getenv("HOME"), line_path, ft_strlen(getenv("HOME"))) == 0)
	{
		home_len = ft_strlen(getenv("HOME"));
		line_path = ft_substr(cwd, home_len - 1, ft_strlen(cwd) - home_len + 1);
		line_path[0] = '~';
		add_galloc(line_path, sh);
	}

	return (line_path);
}

char	*line_finder(t_sh *sh)
{
	char	*line_user;
	char	*line_path;
	char	*line;

	line_user = user_finder(getenv("LOGNAME"), getenv("SESSION_MANAGER"), sh);
	line_path = path_finder(sh);

	line = linejoin(line_user, line_path, sh);
	if (!line)
		return ("?$\n> ");

	return (line);
}
