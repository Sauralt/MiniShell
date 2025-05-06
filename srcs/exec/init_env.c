/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:37:54 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/06 15:32:40 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *data, char **env)
{
	int	i;

	i = 0;
	data->exit_code = 0;
	g_signal_pid = 0;
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
