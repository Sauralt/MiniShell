/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/01 17:12:03 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	while (t->next != data->token)
	{
		if (t->type == 2 && t->next->type == 2)
			return (ft_dprintf(2, "unexpected token %s\n", t->next->str[0]), 2);
		else
			t = t->next;
	}
	if (t->type == 2)
		return (ft_dprintf(2, "unexpected token %s\n", t->next->str[0]), 2);

	return (0);
}
