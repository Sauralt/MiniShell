/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/23 14:18:56 by cfleuret         ###   ########.fr       */
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
	int	flag;

	flag = 0;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
			{
				if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
					flag = 1;
				(*i)++;
			}
			if (line[*i] == '\0')
				return (ft_dprintf(2, "open quote\n"), 2);
		}
		(*i)++;
	}
	if (flag == 1)
		return (quote);
	else
		return ('\0');
}

int	parse_word(t_shell *data, char *line, int *i)
{
	int		start;
	char	*word;
	char	quote;

	start = *i;
	quote = '\0';
	quote = parsing_loop(line, quote, i);
	if (quote == 2)
		return (2);
	word = ft_strndup_no_quote(line, start, *i - start, data);
	if (!word)
		return (1);
	init_list_tok(data, word, quote);
	free(word);
	return (0);
}

int	parsing(t_shell *data, char *line)
{
	int		i;
	int		ret;

	if (line[0] == '\0')
		return (2);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			ret = parse_word(data, line, &i);
			if (ret != 0)
				return (ret);
		}
		else
			i++;
	}
	return (0);
}
