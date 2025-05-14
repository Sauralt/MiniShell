/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/14 16:25:17 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

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
		existing->str = ft_strdup(new_entry);
	}
	else
	{
		ft_add_stack(&data->env, ft_new_stack(new_entry));
	}
	free(new_entry);
}

int	is_valid_identifier_export(const char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_shell *data, t_token *str)
{
	char	*delim;
	int		i;

	if (!str->str[1])
		return (print_env(data->env), 0);
	i = 1;
	while (str->str[i])
	{
		if (str->str[i][0] == '-' && str->str[i][1])
		{
			ft_dprintf(2, "export: `%s': invalid option\n", str->str[i]);
			str->exit_code = 1;
			return (1);
		}
		delim = ft_strchr(str->str[i], '=');
		if (export_norm(data, i, delim, str) == 1)
			return (1);
		if (!delim)
			add_or_replace_env(data, str->str[i], "");
		i++;
	}
	str->exit_code = 0;
	return (0);
}
