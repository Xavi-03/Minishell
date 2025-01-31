#include "../../includes/minishell.h"

/*void	change_value(char *input, t_sh *sh)
{

}*/
//falta cuando pasan "$?"
void	add_var(char *input, t_sh *sh)
{
	t_var	*var_node;
	int		i;

	i = 0;
	if (*input == '=')
		return ;
	var_node = var_addnode(sh);
	var_node->var = galloc(((ft_strlen(input)
		- ft_strlen(ft_strchr(input, '='))) + 1) * sizeof(char), sh);
	while (*input && *input != '=')
		var_node->var[i++] = *(input++);
	input++;
	var_node->value = ft_split(input, ' ');
}

char **found_var(char *input, t_sh *sh)
{
	t_var	*var_iter;
	char 	**value;

	value = NULL;
	var_iter = sh->var_list;
	input++;
	if (ft_strncmp(input, "?", 2) == 0)
		return(ft_split(ft_itoa(sh->last_command), ' ')); // no lo puedo anyadir al galloc
	while (var_iter)
	{
		if (var_iter->var)
		{
			if (ft_strncmp(input, var_iter->var, ft_strlen(input)) == 0)
				value = var_iter->value;
		}
		var_iter = var_iter->next;
	}
	if (!value)
	{
		value = galloc(2 * sizeof(char *), sh);
		value[0] = "";
		value[1] = NULL;
	}
	return (value);
}

t_var	*var_addnode(t_sh *sh)
{
	t_var	*new_node;
	t_var	*node_iter;

	new_node = NULL;
	new_node = var_init(new_node, sh);
	node_iter = sh->var_list;
	while (node_iter->next)
		node_iter = node_iter->next;
	node_iter->next = new_node;
	//sh->var_list = new_node;
	return (new_node);
}

t_var	*var_init(t_var *var_node, t_sh *sh)
{
	var_node = galloc(sizeof(t_var), sh);
	var_node->next = NULL;
	var_node->var = NULL;
	var_node->value = NULL;
	//var_node->value = NULL;
	return (var_node);
}
