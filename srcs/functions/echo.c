/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/20 14:59:06 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_echo(t_token *str)
{
	t_token	*path;

	path = str;
	while (path->next != str)
	{
		printf("%s ", path->next->str);
		path = path->next;
	}
	printf("\n");
	return (0);
}
