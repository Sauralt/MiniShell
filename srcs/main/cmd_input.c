/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:01:42 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:01:42 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX) \
	|| !ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd, INT_MAX) \
	|| !ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env", cmd, INT_MAX) \
	|| !ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

void	exec_builtin(t_shell *data, t_token *cmd)
{
	if (!cmd || !cmd->str)
		return ;

	if (ft_strncmp(cmd->str, "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->str, "env", 4) == 0)
		ft_env();
	else if (ft_strncmp(cmd->str, "cd", 3) == 0)
		ft_cd(data, cmd->next->str);
	else if (ft_strncmp(cmd->str, "echo", 5) == 0)
		ft_echo(cmd->next->str);
//	else if (ft_strncmp(cmd->str, "export", 7) == 0)
//		ft_export(cmd->str);
//	else if (ft_strncmp(cmd->str, "unset", 6) == 0)
//		ft_unset(cmd->next->str);
}

bool	execution(t_shell *data)
{
	t_token	*tmp;

	tmp = data->token;
	if (!tmp)
		return (false);
	if (is_builtin(tmp->str))
	{
		exec_builtin(data, tmp);
		printf("Builtin exécuté : %s\n", tmp->str);
		return (false);

	}
//	free_str(tmp->str);
	return (false);
}
