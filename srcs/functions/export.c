/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/19 14:20:52 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*result;
	size_t	len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len);
	ft_strlcat(result, s2, len);
	ft_strlcat(result, s3, len);
	return (result);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("declare -x %s\n", env->str);
		env = env->next;
	}
}

t_env	*find_env(t_env *env, const char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->str, key, len) == 0 && env->str[len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_or_replace_env(t_shell *data, char *key, char *value)
{
	char	*new_entry;
	t_env	*existing;
	t_env	*new;

	new_entry = ft_strjoin3(key, "=", value);
	if (!new_entry)
		return ;
	existing = find_env(data->env, key);
	if (existing)
	{
		free(existing->str);
		existing->str = new_entry;
	}
	else
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return ;
		new->str = new_entry;
		new->next = data->env;
		new->prev = NULL;
		if (data->env)
			data->env->prev = new;
		data->env = new;
	}
}

int	ft_export(t_shell *data, char *arg)
{
	char	*key;
	char	*value;
	char	*delim;

	delim = ft_strchr(arg, '=');
	if (!arg || !delim || delim == arg)
		return (fprintf(stderr, "export: invalid identifier\n"), 1);
	key = strndup(arg, delim - arg);
	value = ft_strdup(delim + 1);
	if (!key || !value)
		return (free(key), free(value), perror("malloc"), 1);
	add_or_replace_env(data, key, value);
	free(key);
	free(value);
	return (0);
}
