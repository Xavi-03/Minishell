#include "../../includes/minishell.h"

/*void	change_value(char *input, t_sh *sh)
{

}*/
//falta cuando pasan "$?"
/*
void	add_var(char *input, t_sh *sh)
{
	t_var	*var_node;
	int		i;

	if (*input == '=')
		return ;
	var_node = var_addnode(sh);
	var_node->var_name = galloc(((ft_strlen(input)
		- ft_strlen(ft_strchr(input, '='))) + 1) * sizeof(char), sh);
	i = 0;
	while (*input && *input != '=')
		var_node->var_name[i++] = *(input++);
	input++;
	// Horrible hack but extracts content between quotes
	if (ft_strchr(input, '"') || ft_strchr(input, '\''))
		var_node->value = extract_between_chars(sh->line, '\"');
	else
		var_node->value = ft_strdup(input);
	//esto hay que revisarlo y ver cuando meterlo en galloc
}
*/
/*
char	*find_var(char *input, t_sh *sh)
*/
char	**found_var(char *input, t_sh *sh)
{
	t_var	*var_iter;
	char	*value;

	value = NULL;
	var_iter = sh->var_list;
	input++;
	if (ft_strncmp(input, "?", 2) == 0)
		return (ft_split(ft_itoa(sh->last_command), ' '));
	while (var_iter)
	{
		if (var_iter->var_name)
		{
			if (ft_strncmp(input, var_iter->var_name, ft_strlen(input)) == 0)
			{
				value = var_iter->value;
			}
		}
		var_iter = var_iter->next;
	}
	return (ft_split(value, ' '));// poner el nuevo splitter
}

char	*add_var(char *input, int input_idx, t_sh *sh)
{
	t_var	*var_node;
	char	*var_content;

	var_content = sh->input_arr[input_idx + 1];
	if (input[ft_strlen(input) - 1] == '=' && var_content)
	{
		var_node = var_addnode(sh);
		var_node->var_name = galloc(strlen(input), sh);
		var_node->value = add_galloc(ft_strdup(var_content), sh);
		ft_strlcpy(var_node->var_name, input, ft_strlen(input) - 1);
		return (var_node->value);
	}
	return (NULL);
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
	return (new_node);
}

t_var	*var_init(t_var *var_node, t_sh *sh)
{
	var_node = galloc(sizeof(t_var), sh);
	var_node->next = NULL;
	var_node->var_name = NULL;
	var_node->value = NULL;
	return (var_node);
}
