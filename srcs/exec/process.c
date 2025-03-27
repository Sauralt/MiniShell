/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:29:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/27 16:11:35 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(t_shell *data)
{
	dup2(data->token->infile, 0);
	dup2(data->token->outfile, 1);
	exec_abs(data->token->str, data->env);
}
