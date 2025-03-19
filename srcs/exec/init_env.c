/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:37:54 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/19 16:07:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (i == 0)
			data->env = ft_new_stack(env[i]);
		else
			ft_add_stack (&data->env, ft_new_stack(env[i]));
		i++;
	}
	if (!env[0])
		data->env = ft_new_stack(getcwd(NULL, 0));
}
