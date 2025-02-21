/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   galloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 00:22:18 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:46 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	terminate(int exit_value, t_sh *sh)
{
	free_galloc(0, sh);
	free(sh);
	exit(exit_value);
}

void	free_galloc(int level, t_sh *sh)
{
	t_galloc	*temp_galloc;
	t_galloc	*list_galloc;

	list_galloc = sh->l_galloc->start;
	while (list_galloc)
	{
		temp_galloc = list_galloc;
		list_galloc = list_galloc->next;
		if (temp_galloc && temp_galloc->mem && temp_galloc->level >= level)
		{
			free(temp_galloc->mem);
			temp_galloc->mem = NULL;
		}
		if (temp_galloc && 0 == level)
			free(temp_galloc);
	}
}

/*TODO Implement terminate and check if galloc fails*/

void	*add_galloc(void *mem, int level, t_sh *sh)
{
	t_galloc	*new_node;

	if (!mem)
		return (NULL);
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		terminate(EXIT_FAILURE, sh);
	new_node->mem = mem;
	new_node->level = level;
	new_node->next = NULL;
	new_node->start = sh->l_galloc->start;
	sh->l_galloc->next = new_node;
	sh->l_galloc = new_node;
	return (mem);
}

void	gfree(void *ptr, t_sh *sh)
{
	t_galloc	*mem_node;
	t_galloc	*prev_node;

	mem_node = sh->l_galloc->start;
	prev_node = NULL;
	while (mem_node)
	{
		if (mem_node->mem == ptr)
		{
			free(ptr);
			ptr = NULL;
			mem_node->mem = NULL;
			if (prev_node)
				prev_node->next = mem_node->next;
			free(mem_node);
			return ;
		}
		prev_node = mem_node;
		mem_node = mem_node->next;
	}
}

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

/*TODO Implement terminate and check if galloc fails*/

void	*galloc(size_t size, int level, t_sh *sh)
{
	t_galloc	*new_node;
	void		*mem;

	new_node = NULL;
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		terminate(EXIT_FAILURE, sh);
	mem = ft_calloc(1, size);
	if (!mem)
		terminate(EXIT_FAILURE, sh);
	new_node->mem = mem;
	new_node->level = level;
	new_node->next = NULL;
	new_node->start = sh->l_galloc->start;
	sh->l_galloc->next = new_node;
	sh->l_galloc = new_node;
	return (mem);
}
