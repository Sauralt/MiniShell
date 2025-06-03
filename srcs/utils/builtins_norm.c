/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:52:39 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/03 16:53:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(t_env *env)
{
	char	buffer[PATH_SIZE];
	char	*cwd;

	if (getcwd(buffer, sizeof(buffer)))
		return (ft_strdup(buffer));
	cwd = get_env_value(env, "PWD", 3);
	if (cwd && *cwd)
		return (cwd);
	if (cwd)
		free(cwd);
	return (NULL);
}

int	get_current_directory(t_env *env, char *buffer, size_t size)
{
	char	*cwd;

	cwd = ft_getcwd(env);
	if (!cwd)
	{
		ft_dprintf(2, "ft_getcwd: unable to determine current directory\n");
		return (0);
	}
	ft_strlcpy(buffer, cwd, size);
	free(cwd);
	return (1);
}

int	set_env_var_loop(t_env *env, char *new_entry, int key_len, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->str, key, key_len) == 0 && env->str[key_len] == '=')
		{
			free(env->str);
			env->str = new_entry;
			return (1);
		}
		env = env->next;
	}
	if (ft_strncmp(env->str, key, key_len) == 0 && env->str[key_len] == '=')
	{
		free(env->str);
		env->str = new_entry;
		return (1);
	}
	return (0);
}

char	*init_resolved_path(t_shell *data, t_token *t, char *resolved_path)
{
	resolved_path = cd_home(t->str[1]);
	if (resolved_path)
		resolved_path = handle_cd_dash(resolved_path, data);
	return (resolved_path);
}

void	not_pipe(t_shell *data, t_token *t, int *original)
{
	if (ft_strcmp(t->str[0], "exit") == 0)
	{
		close(original[0]);
		close(original[1]);
	}
	if (builtin(data, t, original, 0) == 1 && t->type != 2
		&& t->exit_code == 0)
	{
		if (exec_simple(data, t, original, 0) == 1)
			perror("fork");
	}
	data->exit_code = t->exit_code;
}
