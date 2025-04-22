/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/22 13:43:11 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_regular_char(char **result, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*result = ft_strjoin_free(*result, ft_strdup(tmp));
}

static void	handle_env_var(t_shell *data, char **result,
	const char *input, int *i)
{
	int		j;
	char	*var;
	char	*val;
	t_env	*env;

	j = *i + 1;
	if (input[j] == '?')
	{
		val = ft_itoa(data->exit_code);
		*result = ft_strjoin_free(*result, val);
		*i += 2;
		return ;
	}
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var = ft_substr(input, *i + 1, j - (*i + 1));
	env = find_env(data->env, var);
	val = ft_strchr(env->str, '=');
	if (env && val)
		*result = ft_strjoin_free(*result, ft_strdup(val + 1));
	free(var);
	*i = j;
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
			handle_env_var(data, &result, input, &i);
		else
			handle_regular_char(&result, input[i++]);
	}
	return (result);
}

static bool	handle_line(t_shell *data, int fd, char *buf)
{
	char	*expanded;

	expanded = expand_dollar(data, buf);
	if (!expanded)
	{
		free(buf);
		perror("malloc");
		return (false);
	}
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
	return (true);
}

static bool	read_in_stdin(t_shell *data, int fd, char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			ft_dprintf(2, "warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		if (!handle_line(data, fd, buf))
			return (false);
		free(buf);
	}
	close(fd);
	return (true);
}

void	heredoc(t_shell *data, t_token *t)
{
	int		fd;
	char	*delimiter;

	delimiter = t->next->str[0];
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
	unlink(".heredoc_tmp");
	t->infile = fd;
	if (t->next && t->next->next)
		t->next->type = 2;
}
