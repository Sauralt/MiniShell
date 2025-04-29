/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/29 15:53:13 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_len(char *line)
{
	int	i;
	int	skip;

	i = 0;
	skip = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && line[i + 1] == line[i])
		{
			skip += 2;
			i += 2;
		}
		else
			i++;
	}
	return (skip);
}

char	*remove_closed_quotes(char *line)
{
	char	*newline;
	int		i;
	int		j;
	int		len;
	int		skip;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	skip = skip_len(line);
	newline = malloc(sizeof(char) * (len - skip + 1));
	if (!newline)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && line[i + 1] == line[i])
			i += 2;
		else
			newline[j++] = line[i++];
	}
	newline[j] = '\0';
	return (newline);
}

char	parsing_loop(char*line, char quote, int *i)
{
	while (line[*i] && line[*i] != ' ')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == '\0')
				return (ft_dprintf(2, "open quote\n"), 2);
		}
		(*i)++;
	}
	return (quote);
}

int	parsing(t_shell *data, char *line)
{
	int		i;
	int		start;
	char	*word;
	char	quote;

	if (line[0] == '\0')
		return (2);
	i = 0;
	while (line[i])
	{
		quote = '\0';
		if (line[i] != ' ')
		{
			start = i;
			quote = parsing_loop(line, quote, &i);
			word = ft_strndup_no_quote(line, start, i - start, data);
			if (!word)
				return (ft_dprintf(2, "open quote\n"), 2);
			init_list_tok(data, word, quote);
			free(word);
		}
		else
			i++;
	}
	return (0);
}
