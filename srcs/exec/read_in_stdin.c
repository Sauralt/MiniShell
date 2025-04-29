/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_in_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:02:12 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/29 14:02:37 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	write_heredoc_line(int fd, char *line)
{
	if (write(fd, line, ft_strlen(line)) == -1)
		return (false);
	if (write(fd, "\n", 1) == -1)
		return (false);
	return (true);
}

static bool	process_heredoc_line(t_shell *data, int fd, char *buf)
{
	char	*expanded;

	expanded = expand_dollar(data, buf);
	if (!expanded)
	{
		free(buf);
		perror("malloc");
		return (false);
	}
	if (!write_heredoc_line(fd, expanded))
	{
		free(buf);
		free(expanded);
		perror("write");
		return (false);
	}
	free(buf);
	free(expanded);
	return (true);
}

static bool	handle_eof(char *buf, char *delimiter)
{
	if (!buf)
	{
		ft_dprintf(2,
			"warning: here-document delimited by end-of-file (wanted '%s')\n",
			delimiter);
		return (true);
	}
	return (false);
}

static bool	loop_heredoc(t_shell *data, int fd, char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("heredoc> ");
		if (handle_eof(buf, delimiter))
			break ;
		if (ft_strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break ;
		}
		if (!process_heredoc_line(data, fd, buf))
			return (false);
	}
	return (true);
}

bool	read_in_stdin(t_shell *data, int fd, char *delimiter)
{
	bool	success;

	success = loop_heredoc(data, fd, delimiter);
	close(fd);
	return (success);
}
