/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/28 14:02:38 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strdup_param(t_token *t, int i, char **str, int count)
{
	int	j;

	t->str = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (j < count && str[i] != NULL)
	{
		t->str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	t->str[j] = NULL;
}

static int	is_it_double(char **str, int i, int j)
{
	if (str[i][j] == str[i][j + 1])
		j++;
	else if (str[i][j] != str[i][j + 1]
		&& (str[i][j + 1] == '>' || str[i][j + 1] == '<'))
		return (-1);
	return (j);
}

static char	**check_meta(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i][j])
	{
		if ((str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|'))
		{
			if (j == 0 || str[i][j + 1] == '\0')
				return (str);
			if (str[i][j + 1] == str[i][j] && str[i][j] != '|')
				return (ft_split(str[i], str[i][j]));
			else
				return (ft_split(str[i], str[i][j]));
		}
		j++;
	}
	return (str);
}

static char	**spliting(char **str, char **nstr, int n, int i)
{
	char	**check;
	int		len;
	int		j;

	check = 0;
	len = i + n;
	nstr = malloc(sizeof(char *) * (len + 1));
	i = 0;
	j = 0;
	while (i < len)
	{
		check = check_meta(str, i);
		if (check == str)
			nstr[i] = ft_strdup(str[j]);
		else
		{
			n = 0;
			while (check[n])
			{
				if (check[n] == check[n + 1])
					n++;
				nstr[i] = ft_strdup(check[n]);
				n++;
				i++;
			}
		}
		printf("%d\n", i);
		i++;
		j++;
	}
	nstr[i] = NULL;
	return (nstr);
}

char	**re_split(char **str)
{
	int		n;
	int		i;
	int		j;
	char	**nstr;

	n = 0;
	i = 0;
	nstr = NULL;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|')
			{
				j = is_it_double(str, i, j);
				if (j == -1)
					return (NULL);
				n++;
			}
			j++;
		}
		i++;
	}
	nstr = spliting(str, nstr, n, i);
	i = 0;
	while (str[i])
	{
		printf("%s\n", nstr[i]);
		i++;
	}
	return (nstr);
}
