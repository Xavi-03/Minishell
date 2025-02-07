/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:09:57 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/06 19:43:25 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_set(t_cmd_arr_args *args, t_sh *sh)
{
	char	**cmd_arr;
	char	*str;
	size_t	start;

	start = args->i;
	cmd_arr = args->cmd_arr;
	str = args->str;

	if ((str[args->i] == '>' && str[args->i + 1] == '>')
		|| (str[args->i] == '<' && str[args->i + 1] == '<'))
		args->i += 2;
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
	args->i++;
}

void	second_set(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	char	**cmd_arr;

	start = args->i;
	str = args->str;
	cmd_arr = args->cmd_arr;
	while (!is_in_set(str[args->i], "\'\"|>< ") && str[args->i])
	{
		if (str[args->i + 1] == '=' && is_in_set(str[args->i + 2], "\"\'"))
		{
			args->i += 3;
			while (!is_in_set(str[args->i], "\'\"") && str[args->i])
				args->i++;
		}
		args->i++;
	}
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
}

void	third_set(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	char	**cmd_arr;

	args->i++;
	start = args->i;
	str = args->str;
	cmd_arr = args->cmd_arr;
	while (!is_in_set(str[args->i], "\"|><") && str[args->i])
		args->i++;
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
	args->i++;
}

void	fourth_set(t_cmd_arr_args *args, t_sh *sh)
{
	size_t	start;
	char	*str;
	char	**cmd_arr;

	args->i++;
	start = args->i;
	str = args->str;
	cmd_arr = args->cmd_arr;
	while (!is_in_set(str[args->i], "\'") && str[args->i])
		args->i++;
	if (cmd_arr)
	{
		cmd_arr[args->n_substr] = (char *)galloc(args->i - start + 1, sh);
		ft_strlcpy(cmd_arr[args->n_substr], str + start, args->i - start + 1);
	}
	args->n_substr++;
	args->i++;
}
