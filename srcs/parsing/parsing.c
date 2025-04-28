/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/28 18:55:26 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_closed_quotes(char *line)
{
	char	*newline;
	int		i;
	int		j;
	int		len;
	char	flag;

	i = 0;
	len = ft_strlen(line);
	flag = '\0';
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"')
			&& line[i + 1] == line[i] && flag != line[i])
		{
			len -= 2;
			flag = line[i];
		}
		else if ((line[i] == '\'' || line[i] == '"')
			&& line[i + 1] == line[i] && flag == line[i])
			flag = '\0';
		i++;
	}
	newline = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"')
			&& line[i + 1] == line[i] && flag != line[i])
		{
			i += 2;
			flag = line[i];
		}
		else if ((line[i] == '\'' || line[i] == '"')
			&& line[i + 1] == line[i] && flag == line[i])
		{
			flag = '\0';
			newline[j++] = line[i++];
		}
		else
			newline[j++] = line[i++];
	}
	newline[j] = '\0';
	printf("%s\n", newline);
	return (newline);
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
			while (line[i] && line[i] != ' ')
			{
				if (line[i] == '\'' || line[i] == '"')
				{
					quote = line[i];
					i++;
					while (line[i] && line[i] != quote)
						i++;
					if (line[i] == '\0')
						return (ft_dprintf(2, "open quote\n"), 2);
				}
				i++;
			}
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
