#include "../../includes/minishell.h"

void	terminate(t_sh *sh)
{
	free_galloc(sh);
	free(sh);
}

void	free_galloc(t_sh *sh)
{
	t_galloc	*temp_galloc;
	t_galloc	*list_galloc;

	list_galloc = sh->l_galloc->start;
	while (list_galloc)
	{
		temp_galloc = list_galloc;
		list_galloc = list_galloc->next;
		if (temp_galloc->mem)
			free(temp_galloc->mem);
		if (temp_galloc)
			free(temp_galloc);
	}
}

void	*add_galloc(void *mem, t_sh *sh)
{
	t_galloc	*new_node;

	if (!mem)
		return (NULL);
	if (!sh->l_galloc)
	{
		sh->l_galloc = malloc(sizeof(t_galloc));
		if (!sh->l_galloc)
			return (NULL);// check if first galloc fail;
		sh->l_galloc->next = NULL;
		sh->l_galloc->mem = NULL;
		sh->l_galloc->start = sh->l_galloc;
	}
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		printf("Terminate()"); // implement terminate();
	new_node->mem = mem;
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

	mem_node = sh->l_galloc;
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
		}
		prev_node = mem_node;
		mem_node = mem_node->next;
	}
}

void	*galloc(size_t size, t_sh *sh)
{
	t_galloc	*new_node;
	void		*mem;

	new_node = NULL;
	if (!sh->l_galloc)
	{
		sh->l_galloc = malloc(sizeof(t_galloc));
		if (!sh->l_galloc)
			return (NULL);// check if first galloc fail;
		sh->l_galloc->next = NULL;
		sh->l_galloc->mem = NULL;
		sh->l_galloc->start = sh->l_galloc;
	}
	new_node = malloc(sizeof(t_galloc));
	if (!new_node)
		printf("\"Terminate()\""); // implement terminate();
	mem = malloc(size);
	if (!mem)
		printf("\"Terminate()\""); // implement terminate();
	new_node->mem = mem;
	new_node->next = NULL;
	new_node->start = sh->l_galloc->start;
	sh->l_galloc->next = new_node;
	sh->l_galloc = new_node;
	return (mem);
}
