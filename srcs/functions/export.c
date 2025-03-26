/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/26 16:44:30 by mgarsaul         ###   ########.fr       */
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

t_env	*find_env(t_env *env, const char *key)
{
	size_t	len;
	t_env	*start;

	if (!env)
		return (NULL);
	len = ft_strlen(key);
	start = env;
	while (env)
	{
		if (ft_strncmp(env->str, key, len) == 0 && env->str[len] == '=')
			return (env);
		env = env->next;
		if (env == start)
			break ;
	}
	return (NULL);
}

void	print_env(t_env *env)
{
	t_env	*start;

	if (!env)
		return ;
	start = env;
	while (env)
	{
		printf("declare -x %s\n", env->str);
		env = env->next;
		if (env == start)
			break ;
	}
}

void	add_or_replace_env(t_shell *data, char *key, char *value)
{
	char	*new_entry;
	t_env	*existing;

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
		ft_add_stack(&data->env, ft_new_stack(new_entry));
	}
}

int	ft_export(t_shell *data, t_token *str)
{
	char	*key;
	char	*value;
	char	*delim;
	int		i;

	i = 1;
	while (str->str[i])
	{
		if (ft_strncmp(str->str[i], "export", 7) == 0)
			return (print_env(data->env), 0);
		delim = ft_strchr(str->str[i], '=');
		if (!delim || delim == str->str[i])
			return (fprintf(stderr, "export: invalid identifier\n"), 1);
		key = strndup(str->str[i], delim - str->str[i]);
		value = ft_strdup(delim + 1);
		if (!key || !value)
			return (free(key), free(value), perror("malloc"), 1);
		add_or_replace_env(data, key, value);
		i++;
	}
	free(key);
	free(value);
	return (0);
}
