/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_galloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:41:01 by jtinaut-          #+#    #+#             */
/*   Updated: 2025/02/23 19:41:02 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_galloc(t_sh *sh)
{
	sh->l_galloc = malloc(sizeof(t_galloc));
	if (!sh->l_galloc)
		exit(EXIT_FAILURE);
	sh->l_galloc->next = NULL;
	sh->l_galloc->mem = NULL;
	sh->l_galloc->level = 0;
	sh->l_galloc->start = sh->l_galloc;
}
