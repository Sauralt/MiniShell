/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/23 15:04:03 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *data, char *line)
{
	int		i;
	int		start;
	char	*word;
	char	quote;

	i = 0;
	if (line[0] == '\0')
		return (2);
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
			init_list_tok(data, word);
			free(word);
		}
		else
			i++;
	}
	return (0);
}
