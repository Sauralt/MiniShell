/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/01 19:47:56 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_quote(char **str, char c, int i, int j)
{
	int		len;
	char	*result;

	len = quote_len(str, str[0][1], i, j);
	if (len == -1)
		return (NULL);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	result[0] = c;
	len = 1;
	j++;
	while (str[i] && str[i][j])
	{
		if (str[i][j] == c)
		{
			result[len++] = c;
			break ;
		}
		result[len++] = str[i][j];
		j++;
	}
	result[len] = '\0';
	return (result);
	// while (str[i])
	// {
	// 	j = 0;
	// 	while (str[i][j] && str[i][j])
	// 	{
	// 		if (str[i][j] == c)
	// 		{
	// 			result[len++] = c;
	// 			break ;
	// 		}
	// 		result[len++] = str[i][j];
	// 		j++;
	// 	}
	// 	result[len++] = '\0';
	// 	return (NULL);
	// }
	// result[len] = '\0';
	// return (result);
}

static char	**change_str_quote(char **result, char **str)
{
	int		i;
	int		j;
	int		k;
	int		new_i;
	char	*quote;

	// i = 0;
	// k = 0;
	// while (str[i])
	// {
	// 	j = 0;
	// 	while (str[i][j] != '\'' && str[i][j] != '"')
	// 	{
	// 		if (str[i][j] == '\'' || str[i][j] == '"')
	// 		{
	// 			quote = str_quote(str, str[i][j], i, j);
	// 			result[k++] = quote;
	// 			i = skip(str, str[i][j], i, j);
	// 		}
	// 		j++;
	// 	}
	// 	if (str[i])
	// 		result[k++] = ft_strdup(str[i]);
	// 	i++;
	// }
	// result[k] = NULL;
	// return (result);
	i = 0;
	k = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
			{
				quote = str_quote(str, str[i][j], i, j);
				if (!quote)
					return (NULL);
				result[k++] = quote;
				new_i = skip(str, str[i][j], i, j);
				if (new_i == -1)
					return (NULL);
				i = new_i;
				break ;
			}
			j++;
		}
		if (str[i] && str[i][j] == '\0')
			result[k++] = ft_strdup(str[i]);
		i++;
	}
	result[k] = NULL;
	return (result);
}

char	**ft_quote(char **str)
{
	int		i;
	int		j;
	int		n;
	char	**result;

	i = 0;
	n = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
			{
				printf("test\n");
				if (skip(str, str[i][j], i, j) == -1)
					return (NULL);
				//j = change_j(str, str[i][j], i, j);
				n++;
			}
			j++;
		}
		n++;
		i++;
	}
	result = malloc(sizeof(char *) * (n + 1));
	return (change_str_quote(result, str));
}
