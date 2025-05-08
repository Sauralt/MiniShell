/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>              +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:43:52 by cfleuret            #+#    #+#           */
/*   Updated: 2025/05/08 14:43:52 by cfleuret           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_flag(t_shell *data, t_token *t)
{
	int	flag;

	flag = 0;
	while (t->next != data->token)
	{
		if (t->str[0][0] == '|')
			flag = 1;
		t = t->next;
	}
	t = t->next;
	return (flag);
}
