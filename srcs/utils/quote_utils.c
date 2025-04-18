/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:39 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 12:30:38 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_quote_init(char **str, char c, int i, int *j)
{
	int		len;
	char	*result;

	len = quote_len(str, c, i, *j);
	if (len == -1)
		return (NULL);
	result = malloc(sizeof(char) * (len));
	if (!result)
		return (NULL);
	(*j)++;
	return (result);
}

int	quote_len(char **str, char c, int i, int j)
{
	int	n;

	n = 1;
	j++;
	while (str[i])
	{
		while (str[i][(j)])
		{
			n++;
			if (str[i][j] == c)
				return (n);
			j++;
			n++;
		}
		i++;
		j = 0;
	}
	return (-1);
}

int	skip(char **str, char c, int i, int j)
{
	j++;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == c)
				return (i);
			j++;
		}
		i++;
		j = 0;
	}
	return (-1);
}

int	change_j(char **str, char c, int i, int j)
{
	while (str[i])
	{
		j = 1;
		while (str[i][j])
		{
			if (str[i][j] == c)
				return (j);
			j++;
		}
		i++;
	}
	return (j);
}
