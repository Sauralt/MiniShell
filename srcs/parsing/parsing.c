/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 12:50:52 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *data, char *line)
{
	int		i;
	int		flag;
	int		start;
	char	*word;
	char	quote;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			start = i;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == '\0')
				return (ft_dprintf(2, "open quote\n"), 1);
			word = ft_strndup(line, start, i - start);
			if (quote == '"')
				init_list_tok(data, word, 1);
			else
				init_list_tok(data, word, 0);
			free(word);
			i++;
		}
		else if (line[i] != ' ')
		{
			start = i;
			while (line[i] && line[i] != ' ')
			{
				i++;
				flag = 1;
			}
			word = ft_strndup(line, start, i - start);
			init_list_tok(data, word, flag);
			free(word);
			flag = 0;
		}
		else
			i++;
	}
	return (0);
}
