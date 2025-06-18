/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_norm_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:48:40 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/18 19:00:20 by cfleuret         ###   ########.fr       */
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
	if (flag >= 0)
	{
		if (data->pids)
			free(data->pids);
		if (data->prev_fd > -1)
			close(data->prev_fd);
	}
	free(data);
	rl_clear_history();
}

int	check_numeric(const char *start, const char *str, int sign)
{
	const char	*limit;

	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (0);
	if (start == str)
		return (1);
	if (sign == 1)
		limit = "9223372036854775807";
	else
		limit = "9223372036854775808";
	if (compare_abs_str(start, limit))
		return (0);
	return (1);
}

void	err_msg(t_shell *data, t_token *cmd, int *original, int flag)
{
	if (cmd->infile == -1)
		ft_dprintf(2, "%s: No such file or directory\n", cmd->invalid);
	if (cmd->infile == -2 || cmd->outfile == -2)
		ft_dprintf(2, "%s: Permission denied\n", cmd->invalid);
	if (cmd->infile == -3 || cmd->outfile == -3)
		ft_dprintf(2, "%s: Is a directory\n", cmd->invalid);
	if (flag == -1)
	{
		cmd->exit_code = 1;
		return ;
	}
	if (flag == 0)
		free_exec_simple(data, cmd, original, -1);
	else
		free_exec_simple(data, cmd, original, 1);
}
