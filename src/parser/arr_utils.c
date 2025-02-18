/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:27:29 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:37:00 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_str_arr(char **str_arr)
{
	char	**ptr;

	if (!str_arr)
		return ;
	ptr = str_arr;
	while (*ptr)
		free(*ptr++);
	free(str_arr);
}
