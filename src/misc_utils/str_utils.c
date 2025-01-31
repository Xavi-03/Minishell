#include "../../includes/minishell.h"

char *extract_between_chars(char *str, char c)
{
	char	*ptr_first_c;
	char	*ptr_second_c;
	char	*substr;
	size_t	substr_len;

	ptr_first_c = ft_strchr(str, c);
	if (!ptr_first_c)
		return (NULL);
	ptr_first_c++;
	if (ft_strlen(ptr_first_c) > 2)
		ptr_second_c = ft_strchr(ptr_first_c, c);
	if (!ptr_second_c)
		return (NULL);
	ptr_second_c++;
	substr_len = ptr_second_c - ptr_first_c;
	substr = malloc(substr_len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, ptr_first_c, substr_len);
	return (substr);
}
/*
int	main(void)
{
	char	*str = "\"Hola que tal\" esto es una prueba";

	printf("Var content: %s\n", extract_between_chars(str, '\"'));
	return (0);
}
*/
