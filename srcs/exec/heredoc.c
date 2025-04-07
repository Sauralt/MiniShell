/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:48:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/07 16:05:18 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_first_line(int fd, char *txt)
{
	char	*buffer;
	int		bytes_read;

	if (!txt)
		txt = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (txt);
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		ft_strjoin(txt, buffer);
		free(txt);
		if (ft_strchr(txt, '\n'))
			break ;
	}
	free (buffer);
	return (txt);
}

char	*get(char *txt)
{
	int		i;
	char	*str;

	i = 0;
	if (!txt[i])
		return (NULL);
	while (txt[i] && txt[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (txt[i] && txt[i] != '\n')
	{
		str[i] = txt[i];
		i++;
	}
	if (txt[i] && txt[i] == '\n')
		str[i++] = '\n';
	return (str);
}

char	*clean_first_line(char *txt)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (txt[i] && txt[i] != '\n')
		i++;
	if (!txt[i])
	{
		free (txt);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(txt) - i + 1), sizeof(*txt));
	if (!str)
		return (NULL);
	while (txt[++i])
		str[j++] = txt[i];
	str[j] = '\0';
	free (txt);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*output;
	static char	*txt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	txt = read_first_line(fd, txt);
	if (!txt)
		return (NULL);
	output = get(txt);
	txt = clean_first_line(txt);
	return (output);
}

void	heredoc(t_token *cmd)
{
	char	*line;
	int		fd;
	char	*delimiter;

	if (!cmd || !cmd->str)
		return ;
	delimiter = *cmd->str;
	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc: open");
		return ;
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		line[strcspn(line, "\n")] = 0;

		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	free(*(cmd->str));
	*(cmd->str) = ft_strdup("/tmp/.heredoc_tmp");
}
