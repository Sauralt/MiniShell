/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/18 17:46:23 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_echo(t_shell *data, t_token *str)
{
	t_token	*path;
	t_env  *env;

	path = str;
	while (path->next != str)
	{
		if (path->next->type == 3)

		printf("%s ", path->next->str);
		path = path->next;
	}
	printf("\n");
	return (0);
}
