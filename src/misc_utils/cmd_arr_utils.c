/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:04:34 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/04 00:04:06 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_between_chars(char *str, char c)
{
	char	*ptr_first_c;
	char	*ptr_second_c;
	char	*substr;
	size_t	substr_len;

	ptr_first_c = ft_strchr(str, c);
	if (!ptr_first_c)
		return (NULL);
	ptr_first_c++;
	if (ft_strlen(ptr_first_c) < 2)
		return (NULL);
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

bool	is_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (true);
		set++;
	}
	return (false);
}

char	**create_cmd_arr(char **cmd_arr, size_t n_substr)
{
	if (!cmd_arr)
	{
		cmd_arr = (char **)malloc(sizeof(char *) * (n_substr + 1));
		if (!cmd_arr)
			return (NULL);
		cmd_arr[n_substr] = NULL;
	}
	return (cmd_arr);
}

char	**prepare_cmd_arr(char *str)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	n_substr;
	char	**cmd_arr;

	j = 0;
	cmd_arr = NULL;
	while (j < 2)
	{
		i = 0;
		n_substr = 0;
		while (str[i])
		{
			if (is_in_set(str[i], "|><"))
			{
				if (cmd_arr)
				{
					cmd_arr[n_substr] = (char *)malloc(2);
					ft_strlcpy(cmd_arr[n_substr], str + i, 2);
				}
				n_substr++;
				i++;
			}
			else if (!is_in_set(str[i], "\'\" "))
			{
				start = i;
				while (!is_in_set(str[i], "\'\"|>< ") && str[i])
				{
					if (str[i + 1] == '=' && is_in_set(str[i + 2], "\"\'"))
					{
						i += 3;
						while (!is_in_set(str[i], "\'\"") && str[i])
							i++;
					}
					i++;
				}
				if (cmd_arr)
				{
					cmd_arr[n_substr] = (char *)malloc(i - start + 1);
					ft_strlcpy(cmd_arr[n_substr], str + start, i - start + 1);
				}
				n_substr++;
			}
			else if (str[i] == '\"')
			{
				i++;
				start = i;
				while (!is_in_set(str[i], "\"|><") && str[i])
					i++;
				if (cmd_arr)
				{
					cmd_arr[n_substr] = (char *)malloc(i - start + 1);
					ft_strlcpy(cmd_arr[n_substr], str + start, i - start + 1);
				}
				n_substr++;
				i++;
			}
			else if (str[i] == '\'')
			{
				i++;
				start = i;
				while (!is_in_set(str[i], "\'") && str[i])
					i++;
				if (cmd_arr)
				{
					cmd_arr[n_substr] = (char *)malloc(i - start + 1);
					ft_strlcpy(cmd_arr[n_substr], str + start, i - start + 1);
				}
				n_substr++;
				i++;
			}
			else
				i++;
		}
		cmd_arr = create_cmd_arr(cmd_arr, n_substr);
		j++;
	}
	return (cmd_arr);
}

/*
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	**cmd_arr;
	char	*line;

	while (true)
	{
		line = readline("testshell > ");
		//line = "<cmd_arr_utils.c cat|wc|c";
		cmd_arr = prepare_cmd_arr(line);
		while (*cmd_arr)
			printf("Var content: %s\n", *cmd_arr++);
	}
	return (0);
}
*/
