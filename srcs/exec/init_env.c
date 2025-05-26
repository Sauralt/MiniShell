/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:37:54 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/26 15:38:55 by cfleuret         ###   ########.fr       */
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

void	ft_check_signals(t_shell *data)
{
	if (g_signal_pid == 2)
		data->exit_code = 130;
	if (data->exit_code == 131)
		ft_dprintf(2, "Quit (core dumped)\n");
	g_signal_pid = 0;
}
