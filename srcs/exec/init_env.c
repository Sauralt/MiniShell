/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:37:54 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/23 14:09:36 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_env(char **env)
{
	int	i;

	i = 0;
	data->exit_code = 0;
	g_signal_pid = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_env(t_shell *data, char **env)
{
	int		i;
	char	*temp;
	char	*cwd;

	g_signal_pid = 0;
	if (!(*env) || ft_check_env(env) == 1)
	{
		cwd = getcwd(NULL, 0);
		temp = ft_strjoin("PWD=", cwd);
		data->env = ft_new_stack(temp);
		ft_add_stack(&data->env, ft_new_stack("SHLVL=0"));
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
			ft_add_stack(&data->env, ft_new_stack(env[i]));
		i++;
	}
}

void	ft_check_signals(t_shell *data)
{
	if (g_signal_pid == 2)
		data->exit_code = 130;
	g_signal_pid = 0;
}

int	ft_check_oldpwd(t_env *env)
{
	t_env	*t;

	t = env;
	while (t->next != env)
	{
		if (ft_strncmp(t->str, "OLDPWD=", 7) == 0)
			return (0);
		t = t->next;
	}
	if (ft_strncmp(t->str, "OLDPWD=", 7) == 0)
		return (0);
	return (1);
}

int	ft_check_path(t_env *env)
{
	t_env	*t;

	t = env;
	while (t->next != env)
	{
		if (ft_strncmp(t->str, "PATH=", 5) == 0)
			return (0);
		t = t->next;
	}
	if (ft_strncmp(t->str, "PATH=", 5) == 0)
		return (0);
	return (1);
}
