/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/05 18:09:40 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->type == 2)
	{
		data->exit_code = 2;
		return (ft_dprintf(2, "syntax error near unexpected token `%s'\n", t->str[0]), 2);
	}
	while (t->next != data->token)
	{
		if (t->type == 2 && t->next->type == 2)
		{
			data->exit_code = 2;
			return (ft_dprintf(2, "syntax error near unexpected token `%s'\n", t->next->str[0]), 2);
		}
		t = t->next;
	}
	if (t->type == 2)
	{
		data->exit_code = 2;
		return (ft_dprintf(2, "syntax error near unexpected token `newline'\n"), 2);
	}

	return (0);
}

