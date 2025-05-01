/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/01 15:42:06 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	while (t->next != data->token)
	{
		if ((t->type == 2 && t->next->type == 2)
			|| (t->type == 2 && t->next == data->token))
			return (ft_dprintf(2, "unexpected token `%s'\n", t->str[0]), 2);
		else
			t = t->next;
	}
	return (0);
}
