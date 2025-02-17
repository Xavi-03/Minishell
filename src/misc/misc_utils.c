/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:44:30 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/17 20:44:21 by pohernan         ###   ########.fr       */
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

int	count_tokens(t_token *token_arr)
{
	int	i;

	i = -1;
	while(token_arr[++i])
		;
	return (i);
}
