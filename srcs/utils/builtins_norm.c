/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:52:39 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/09 10:50:20 by mgarsaul         ###   ########.fr       */
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

// int	export_norm(t_shell *data, int i, char *delim, t_token *str)
// {
// 	char	*key;
// 	char	*value;

// 	if (delim == str->str[i] || !is_valid_identifier_export(str->str[i]))
// 	{
// 		ft_dprintf(2, "export: `%s': not a valid identifier\n", str->str[i]);
// 		str->exit_code = 1;
// 		i++;
// 	}
// 	if (delim)
// 	{
// 		key = strndup(str->str[i], delim - str->str[i]);
// 		value = ft_strdup(delim + 1);
// 		if (!key || !value)
// 			return (free(key), free(value), perror("malloc"), 1);
// 		add_or_replace_env(data, key, value);
// 		free(key);
// 		free(value);
// 	}
// 	return (0);
// }

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

