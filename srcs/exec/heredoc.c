/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 11:32:55 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*expand_dollar(t_shell *data, char *input)
{
	int		i;
	char	*result;
	char	*var;
	char	*val;
	int		j;
	t_env	*env;

	i = 0;
	result = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			j = i + 1;
			if (input[j] == '?')
			{
				val = ft_itoa(data->exit_code);
				result = ft_strjoin_free(result, val);
				i += 2;
				continue ;
			}
			while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
				j++;
			var = ft_substr(input, i + 1, j - (i + 1));
			env = find_env(data->env, var);
			if (env && (val = ft_strchr(env->str, '=')))
				result = ft_strjoin_free(result, ft_strdup(val + 1));
			free(var);
			i = j;
		}
		else
		{
			char	tmp[2] = {input[i], '\0'};
			result = ft_strjoin_free(result, ft_strdup(tmp));
			i++;
		}
	}
	return (result);
}


static bool	read_in_stdin(t_shell *data, int fd, char *delimiter)
{
	char	*buf;
	char	*expanded;

	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			ft_dprintf(2, "warning: here-document \
				delimited by end-of-file (wanted '%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		expanded = expand_dollar(data, buf);
		if (!expanded)
		{
			free(buf);
			perror("malloc");
			return (false);
		}
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);

		free(buf);
		free(expanded);
	}
	close(fd);
	return (true);
}

void	heredoc(t_shell *data, char *delimiter)
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
	data->token->infile = fd;
	data->token->next->next->type = 2;
}
