/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:37:54 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/27 14:01:15 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *data, char **env)
{
	int		i;
	char	*temp;
	char	*cwd;

	data->exit_code = 0;
	g_signal_pid = 0;
	if (!(*env) || (env[0] && env[1] && !env[2]))
	{
		cwd = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", cwd);
		data->env = ft_new_stack(temp);
		free(temp);
		free(cwd);
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (i == 0)
			data->env = ft_new_stack(env[i]);
		else
			ft_add_stack (&data->env, ft_new_stack(env[i]));
		i++;
	}
}

void	ft_check_signals(t_shell *data)
{
	if (g_signal_pid == 2)
		data->exit_code = 130;
	if (data->exit_code == 131)
		ft_dprintf(2, "Quit (core dumped)\n");
	g_signal_pid = 0;
}
