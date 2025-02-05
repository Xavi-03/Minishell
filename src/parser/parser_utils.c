#include "../../includes/minishell.h"

void	parse_file_redir(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (cmd->f_next_infile > 0)
	{
		if (cmd->f_next_infile == DOUBLE_REDIR)
			cmd->fd_in_red = 1;
		cmd->f_next_infile = 0;
		cmd->infile = ft_strdup(input);
		add_galloc(cmd->infile, sh);
	}
	else if (cmd->f_next_outfile > 0)
	{
		if (cmd->f_next_outfile == DOUBLE_REDIR)
			cmd->fd_out_red = 1;
		cmd->f_next_outfile = 0;
		cmd->outfile = ft_strdup(input);
		add_galloc(cmd->outfile, sh);
	}
}

void	check_in_out_file(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (ft_strncmp(input, "<", 2) == 0)
		cmd->f_next_infile = SINGLE_REDIR;
	else if (ft_strncmp(input, "<<", 3) == 0)
		cmd->f_next_infile = DOUBLE_REDIR;
	else if (ft_strncmp(input, ">", 2) == 0)
		cmd->f_next_outfile = SINGLE_REDIR;
	else if (ft_strncmp(input, ">>", 3) == 0)
		cmd->f_next_outfile = DOUBLE_REDIR;
	else
		parse_file_redir(input, sh);
}

int	check_std_redir(char *input, t_sh *sh)
{
	t_cmd	*cmd;

	cmd = sh->cmd_list;
	if (ft_strncmp(input, ">", 2) == 0 || ft_strncmp(input, "<", 2) == 0 \
		|| ft_strncmp(input, ">>", 3) == 0 || ft_strncmp(input, "<<", 3) == 0 \
		|| cmd->f_next_infile > 0 || cmd->f_next_outfile > 0)
		return (1);
	return (0);
}
