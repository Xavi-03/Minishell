#include "../includes/minishell.h"

char	*ft_idk(char *src, char c)
{
	char	*str;
	int		i;

	i = -1;
	src++;
	while (src[++i] && src[i] != c)
		;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (src[++i] && src[i] != c)
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}

char	*user_finder()
{
	char	*user;
	char	*pc;
	char	*line_user;

	user = "?";
	pc = "?";

	user = ft_idk(strchr(getenv("SESSION_MANAGER"), '='), '\0');
	pc = ft_idk(strchr(getenv("LOGNAME"), '/'), ':');
	if (!user)
		user = "?";
	if (!pc)
		pc = "?";
	line_user = ft_strjoin(user, ft_strjoin("@", pc));
	if (!line_user)
		return ("?");
	return (line_user);
}

char	*path_finder()
{
	char	*path;
	char	*line_path;

	path = NULL;
	path = strchr(getenv("PWD"), '=');
	if (!path)
		return ("?");
	line_path = malloc((strlen(path) + 1) * sizeof(char));
	if (!line_path)
		return ("?");
	ft_strlcpy(line_path, path, ft_strlen(path) + 1);
	return (line_path);
}

char	*line_finder()
{
	char	*line_user;
	char	*line_path;
	char	*line;

	line_user = user_finder();
	line_path = path_finder();
	line = malloc((strlen(line_user) + strlen(line_path) + 5) * sizeof(char));
	if (!line)
		return ("?$\n>");
	line = ft_strjoin(line_user, ft_strjoin(":", ft_strjoin(line_path, "$\n>")));
	return (line);
}

int	main(void)
{
	char	*input;
	char	*line;

	while(1)
	{
		line = line_finder();
		if (!line)
			line = "?";
		printf("%s\n", line);
		input = readline(line);
		if (!input)
			return (1);
		printf("%s\n", input);
		free(input);
	}
}