/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:16:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/19 16:08:04 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_env(t_shell *data)
{
	t_env	*t;

	t = data->env->next;
	printf("%s\n", data->env->str);
	while (t != data->env)
	{
		printf("%s\n", t->str);
		t = t->next;
	}
	return (0);
}
