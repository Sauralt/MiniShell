/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:16:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/17 13:12:55 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_env(t_shell *data)
{
	t_env	*t;

	t = data->env->next;
	while (t != data->env)
	{
		printf("%s\n", t->str);
		t = t->next;
	}
	return (0);
}
