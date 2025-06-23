/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/12 16:30:14 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_proc(t_shell *data, t_token *cmd, int *original, int flag)
{
	if ((cmd->infile < 0 || cmd->outfile < 0))
		err_msg(data, cmd, original, 1);
	signal(SIGQUIT, SIG_DFL);
	close_origin(original);
	exec_built(data, cmd, flag);
	exit_proc(data, 0, 0, cmd);
}

void	exec_error(t_shell *data, t_token *cmd, int *original, int flag)
{
	if (flag == 0)
		err_msg(data, cmd, original, 0);
	else
		err_msg(data, cmd, original, 1);
}
