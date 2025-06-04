/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:03:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/04 15:40:54 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waitall(t_shell *data)
{
	int	status;
	int	i;

	if (data->prev_fd != -1)
	{
		close(data->prev_fd);
		data->prev_fd = -1;
	}
	i = 0;
	while (i < data->l)
	{
		waitpid(data->pids[i], &status, 0);
		if (i == data->l - 1)
		{
			if (WIFEXITED(status) && data->exit_code)
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) && data->exit_code)
				data->exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	ft_waitpid(pid_t pid, t_token *cmd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		cmd->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->exit_code = 128 + WTERMSIG(status);
	else
		cmd->exit_code = 1;
}

char	*ft_shlvl(char *env)
{
	int		i;
	char	*prefix;
	char	*temp;
	char	*new;
	int		value;

	i = 0;
	while (env[i] && !ft_isdigit(env[i]))
		i++;
	prefix = ft_substr(env, 0, i);
	if (!prefix)
		return (NULL);
	value = ft_atoi(env + i);
	value++;
	temp = ft_itoa(value);
	if (!temp)
		return (free(prefix), NULL);
	new = ft_strjoin(prefix, temp);
	free(prefix);
	free(temp);
	return (new);
}
