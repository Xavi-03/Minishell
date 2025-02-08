/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:04:34 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/06 21:27:30 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_between_chars(char *str, char c, t_sh *sh)
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
	substr = galloc(substr_len + 1, sh);
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

char	**create_cmd_arr(char **cmd_arr, size_t n_substr, t_sh *sh)
{
	if (!cmd_arr)
	{
		cmd_arr = (char **)galloc((n_substr + 1) * sizeof(char *), sh);
		cmd_arr[n_substr] = NULL;
	}
	return (cmd_arr);
}

void	cmd_arr_args_init(t_cmd_arr_args *args, char *str)
{
	args->j = 0;
	args->cmd_arr = NULL;
	args->str = str;
}

char	**prepare_cmd_arr(char *str, t_sh *sh)
{
	t_cmd_arr_args	args;

	cmd_arr_args_init(&args, str);
	while (args.j < 2)
	{
		args.i = 0;
		args.n_substr = 0;
		while (str[args.i])
		{
			if (is_in_set(str[args.i], "|><"))
				process_redirs(&args, sh);
			else if (!is_in_set(str[args.i], "\'\" "))
				process_everything_else(&args, sh);
			else if (str[args.i] == '\"')
				process_double_quotes(&args, sh);
			else if (str[args.i] == '\'')
				process_single_quotes(&args, sh);
			else
				args.i++;
		}
		args.cmd_arr = create_cmd_arr(args.cmd_arr, args.n_substr, sh);
		args.j++;
	}
	return (args.cmd_arr);
}
