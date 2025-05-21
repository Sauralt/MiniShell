/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/05 15:40:39 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_exit_code(t_shell *data, char *result, int *i)
{
	char	*val;

	val = ft_itoa(data->exit_code);
	result = ft_strjoin_free(result, val);
	*i += 2;
	return (result);
}

static char	*expand_variable(t_shell *data, char *input, int *i, char *result)
{
	int		j;
	char	*var;
	char	*val;
	t_env	*env;

	j = *i + 1;
	val = NULL;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var = ft_substr(input, *i + 1, j - (*i + 1));
	env = find_env(data->env, var);
	if (env)
	{
		val = ft_strchr(env->str, '=');
		if (val)
			result = ft_strjoin_free(result, ft_strdup(val + 1));
	}
	free(var);
	*i = j;
	return (result);
}

static char	*append_char(char *result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin_free(result, ft_strdup(tmp)));
}

char	*expand_dollar(t_shell *data, char *input)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			if (input[i + 1] == '?')
				result = expand_exit_code(data, result, &i);
			else
				result = expand_variable(data, input, &i, result);
		}
		else
		{
			result = append_char(result, input[i]);
			i++;
		}
	}
	return (result);
}

void	heredoc(t_shell *data, t_token *t, char *delimiter)
{
	int	fd;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		data->exit_code = 1;
		return ;
	}
	if (!read_in_stdin(data, fd, delimiter))
	{
		unlink(".heredoc_tmp");
		data->exit_code = 1;
		return ;
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc: reopen");
		data->exit_code = 1;
		return ;
	}
	unlink(".heredoc_tmp");
	heredoc_norm(data, t, fd);
}
