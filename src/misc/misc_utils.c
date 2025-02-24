/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:44:30 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 21:49:06 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

size_t	count_chars(char *str, char c)
{
	size_t	n_chars;

	n_chars = 0;
	while (*str)
	{
		if (*str == c)
			n_chars++;
		str++;
	}
	return (n_chars);
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
/*
int	count_tokens(t_token **token_arr)
{
	int	i;

	i = -1;
	while (token_arr[++i])
		;
	return (i);
}
*/

char	*arr_to_str(char **arr, t_sh *sh)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	j = 0;
	while (arr[++i])
	{
		j += ft_strlen(arr[i]);
		if (arr[i + 1])
			j += 1;
	}
	new_str = galloc((j + 1) * sizeof(char), 1, sh);
	new_str[0] = '\0';
	i = -1;
	j = -1;
	while (*arr)
	{
		ft_strlcat(new_str, *arr, ft_strlen(new_str) + 2 + ft_strlen(*arr));
		if (arr[1])
			ft_strlcat(new_str, " ", ft_strlen(new_str) + 2);
		arr++;
	}
	return (new_str);
}
