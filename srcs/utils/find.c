/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:37:50 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/02 17:37:54 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_env_str(t_env *env)
{
	int		i;
	int		j;
	char	**envp;
	t_env	*t;

	i = 1;
	j = -1;
	t = env->next;
	while (t != env)
	{
		i++;
		t = t->next;
	}
	envp = malloc(sizeof(char *) * (i + 2));
	if (!envp)
		return (0);
	while (j++ < i)
	{
		envp[j] = ft_strdup(t->str);
		if (!envp[j])
			return (0);
		t = t->next;
	}
	envp[j] = NULL;
	return (envp);
}

static char	**collect_path(t_env *env)
{
	t_env	*t;
	char	**paths;

	paths = NULL;
	t = env;
	while (t != env->prev && ft_strnstr(t->str, "PATH=", 5) == 0)
		t = t->next;
	if (t->next != env)
		paths = ft_split(t->str + 5, ':');
	return (paths);
}

char	*find_path(char *cmd, t_env *env, int i)
{
	char	**paths;
	char	*path;
	char	*part_path;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = collect_path(env);
	if (!paths)
		return (0);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_str(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_str(paths);
	return (0);
}

int	last_check(t_shell *data)
{
	if (data->token->str[0][0] == '!')
	{
		if (data->token->next == data->token)
			return (2);
		else if (ft_strcmp(data->token->next->str[0], data->token->str[0]) == 0)
		{
			ft_dprintf(2, "parse error near: !\n");
			return (2);
		}
		else
			delone(data, data->token);
	}
	if (data->token->str[0][0] == ':')
		return (2);
	return (0);
}
