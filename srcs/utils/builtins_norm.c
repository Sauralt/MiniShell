/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:52:39 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/15 17:28:56 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_current_directory(char *buffer, size_t size)
{
	if (getcwd(buffer, size) == NULL)
	{
		perror("getcwd");
		return (0);
	}
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
	return (0);
}

int	export_norm(t_shell *data, int i, char *delim, t_token *str)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!str->str[i] || delim == str->str[i]
		|| !is_valid_identifier_export(str->str[i]))
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", str->str[i]);
		str->exit_code = 1;
		return (1);
	}
	if (delim)
	{
		if (delim < str->str[i] || delim > str->str[i] + ft_strlen(str->str[i]))
			return (ft_dprintf(2, "export: internal error\n"), 1);
		key = strndup(str->str[i], delim - str->str[i]);
		value = ft_strdup(delim + 1);
		if (!key || !value)
			return (free(key), free(value), perror("malloc"), 1);
		add_or_replace_env(data, key, value);
		free(key);
		free(value);
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
	if (builtin(data, t, 0, original) == 1 && t->type != 2
		&& t->exit_code == 0)
	{
		if (exec_simple(data, t, original) == 1)
			perror("fork");
	}
	data->exit_code = t->exit_code;
}
