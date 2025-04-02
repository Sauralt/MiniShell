/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:43:39 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/02 17:48:53 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_len(char **str, char c, int i, int j)
{
	int	n;

	n = 1;
	j++;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == c)
				return (n + 1);
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
		j = 0;
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
