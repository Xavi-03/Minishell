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
		add_galloc(redir->infile, 0, sh);
	}
	else if (redir->f_next_outfile > 0)
	{
		if (redir->f_next_outfile == DOUBLE_REDIR)
			redir->fd_out_red = 1;
		redir->f_next_outfile = 0;
		redir->outfile = ft_strdup(input);
		add_galloc(redir->outfile, 0, sh);
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

int	static	char_to_int(char *str_nbr, int i, int flag, t_sh *sh)
{
	if (i > 19 || i == 0)
		return (1);
	if (flag)
	{
		if (ft_strncmp(str_nbr, "9223372036854775808", 20) > 0 && i == 19)
			return (1);
		sh->exit_value = -ft_atoi(str_nbr);
		return (0);
	}
	if (ft_strncmp(str_nbr, "9223372036854775807", 20) > 0 && i == 19)
		return (1);
	sh->exit_value = ft_atoi(str_nbr);
	return (0);
}

int	parser_int(char *str_nbr, t_sh *sh)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (*str_nbr == '-' || *str_nbr == '+')
	{
		if (*str_nbr == '-')
			flag = 1;
		str_nbr++;
	}
	while (str_nbr[0] == '0' && str_nbr[1] != '\0')
		str_nbr++;
	while (str_nbr[i])
	{
		if (!ft_isdigit(str_nbr[i]))
			return (1);
		i++;
	}
	return(char_to_int(str_nbr, i, flag, sh));
}
