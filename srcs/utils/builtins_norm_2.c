/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:48:40 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/03 17:09:28 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		key = ft_strndup(str->str[i], 0, delim - str->str[i]);
		value = ft_strdup(delim + 1);
		if (!key || !value)
			return (free(key), free(value), perror("malloc"), 1);
		add_or_replace_env(data, key, value);
		free(key);
		free(value);
	}
	return (0);
}

void	free_exit(t_shell *data, int flag)
{
	free_tokens(data->token);
	free_env(data->env);
	if (flag > 0)
	{
		if (data->pids)
			free(data->pids);
		if (data->prev_fd > -1)
			close(data->prev_fd);
	}
	free(data);
	rl_clear_history();
}
