/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:39:38 by pohernan          #+#    #+#             */
/*   Updated: 2025/02/18 18:37:02 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_file_redir(char *input, t_sh *sh)
{
	t_redir	*redir;

	redir = sh->cmd_list->redir_list;
	if (redir->f_next_infile > 0)
	{
		if (redir->f_next_infile == DOUBLE_REDIR)
			redir->fd_in_red = 1;
		redir->f_next_infile = 0;
		redir->infile = ft_strdup(input);
		add_galloc(redir->infile, sh);
	}
	else if (redir->f_next_outfile > 0)
	{
		if (redir->f_next_outfile == DOUBLE_REDIR)
			redir->fd_out_red = 1;
		redir->f_next_outfile = 0;
		redir->outfile = ft_strdup(input);
		add_galloc(redir->outfile, sh);
	}
}

void	check_in_out_file(char *input, t_sh *sh)
{
	t_redir	*redir;

	printf("input: %s\n", input);
	redir = sh->cmd_list->redir_list;
	if ((*input == '<' || *input == '>') \
		&& (redir->f_next_infile || redir->f_next_outfile))
		sh->syntax_error = 1;
	if (redir->infile || redir->outfile)
		redir = redir_addnode(sh);
	if (ft_strncmp(input, "<", ft_strlen(input)) == 0)
		redir->f_next_infile = SINGLE_REDIR;
	else if (ft_strncmp(input, "<<", ft_strlen(input)) == 0)
		redir->f_next_infile = DOUBLE_REDIR;
	else if (ft_strncmp(input, ">", ft_strlen(input)) == 0)
		redir->f_next_outfile = SINGLE_REDIR;
	else if (ft_strncmp(input, ">>", ft_strlen(input)) == 0)
		redir->f_next_outfile = DOUBLE_REDIR;
	else
		parse_file_redir(input, sh);
}

int	check_std_redir(char *input, t_sh *sh)
{
	t_redir	*redir;

	redir = sh->cmd_list->redir_list;
	if (ft_strncmp(input, ">", 2) == 0 || ft_strncmp(input, "<", 2) == 0 \
		|| ft_strncmp(input, ">>", 3) == 0 || ft_strncmp(input, "<<", 3) == 0 \
		|| redir->f_next_infile > 0 || redir->f_next_outfile > 0)
		return (1);
	return (0);
}
