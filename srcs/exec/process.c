/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/12 16:06:05 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(char *cmd, char **env)
{
	char	*path;
	int		i;

	path = find_path(cmd, env, i);
	if (!path)
	{
		ft_printf(2, "%s: command not found\n", cmd[0]);
		free_str(cmd);
		return (1);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_printf(2, "%s: command not found\n", cmd[0]);
		free_str(cmd);
		return (1);
	}
	return (0);
}

int	proc(t_shell *data)
{
	execute(data->cmd->str, data->env);
	return (0);
}
