/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/31 17:11:13 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token *t)
{
	int	infile;

	infile = open("heredoc.tmp", O_CREAT, O_WRONLY, O_TRUNC);
}
