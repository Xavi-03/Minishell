/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_recursive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 21:51:51 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/24 21:52:39 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	recursive_expand_var(t_token **token_arr, t_sh *sh)
{
	int	i;

	i = -1;
	while (token_arr[++i])
	{
		if (token_arr[i]->is_variable)
			recursive_expand_var(found_var(token_arr[i]->str, sh), sh);
		else
			cmd_parser(token_arr[i], sh);
	}
}
