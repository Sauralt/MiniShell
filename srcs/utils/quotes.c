/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/03 15:12:03 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_quote(char **str, char c, int i, int j)
{
	int		len;
	char	*result;
	int		k;

	k = 0;
	len = quote_len(str, c, i, j);
	if (len == -1)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[k++] = c;
	j++;

	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == c)
			{
				result[k++] = c;
				result[k] = '\0';
				return (result);
			}
			result[k++] = str[i][j];
			j++;
		}
		i++;
		j = 0;
		if (str[i])
			result[k++] = ' ';
	}

	free(result);
	return (NULL);
}

static char	**change_str_quote(char **result, char **str)
{
	int		i;
	int		j;
	int		k;
	int		new_i;
	char	*quote;

	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '\'' || str[i][j] == '"')
		{
			quote = str_quote(str, str[i][j], i, j);
			if (!quote)
				return (NULL);
			result[k++] = quote;
			new_i = skip(str, str[i][j], i, j);
			if (new_i == -1)
				return (NULL);
			i = new_i + 1;
		}
		while (str[i] && (str[i][0] != '\'' && str[i][0] != '"'))
		{
			result[k++] = ft_strdup(str[i]);
			i++;
		}
	}
	result[k] = NULL;
	return (result);
}


char	**ft_quote(char **str)
{
	int		i;
	int		j;
	int		new_i;
	int		n;
	char	**result;

	i = 0;
	n = 0;
	new_i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
			{
				if (new_i == 0)
				{
					new_i = skip(str, str[i][j], i, j);
					i = new_i;
					j = change_j(str, str[i][j], i, j);
					n++;
				}
				if (new_i == -1)
					return (NULL);
			}
			j++;
		}
		n++;
		i++;
	}
	result = malloc(sizeof(char *) * (n + 1));
	if (!result)
		return (NULL);
	return (change_str_quote(result, str));
}
