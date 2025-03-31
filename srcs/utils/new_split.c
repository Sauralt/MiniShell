/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:19:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/31 16:22:34 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_it_double(char **str, int i, int j)
{
	if (str[i][j] == str[i][j + 1])
		j++;
	else if (str[i][j] != str[i][j + 1]
		&& (str[i][j + 1] == '>' || str[i][j + 1] == '<'))
		return (-1);
	return (j);
}

static char	*ft_parse(char **str, int i, int j)
{
	char	*s;
	int		len;

	j = 0;
	len = ft_strlen(str[i]);
	while (str[i][j])
	{
		if ((str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|'))
		{
			len++;
			if (str[i][j + 1] == str[i][j] && str[i][j] != '|')
				j++;
		}
		j++;
	}
	j = 0;
	s = malloc(sizeof(char) * (len + 2));
	len = 0;
	while (str[i][j])
	{
		if ((str[i][j + 1] == '<' || str[i][j + 1] == '>'
			|| str[i][j + 1] == '|') && str[i][j + 1] != str[i][j])
		{
			s[len] = str[i][j];
			len++;
			s[len] = ' ';
		}
		else if (str[i][j] == '<' || str[i][j] == '>'
			|| str[i][j] == '|')
		{
			if (str[i][j + 1] != str[i][j])
			{
				s[len] = str[i][j];
				len++;
				s[len] = ' ';
			}
			else
			{
				s[len] = str[i][j];
				len++;
				j++;
				s[len] = str[i][j];
				len++;
				s[len] = ' ';
			}
		}
		else
			s[len] = str[i][j];
		len++;
		j++;
	}
	s[len] = '\0';
	return (s);
}

static char	**check_meta(char **str, int i)
{
	int		j;
	char	*s;

	j = 0;
	while (str[i][j])
	{
		if ((str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|'))
		{
			if (j == 0 && str[i][j + 1] == '\0')
				return (str);
			else
			{
				s = ft_parse(str, i, j);
				return (ft_split(s, ' '));
			}
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
	int		k;

	check = 0;
	len = i + n + 1;
	nstr = malloc(sizeof(char *) * len);
	i = 0;
	j = 0;
	k = 0;
	while (i < len - 1)
	{
		check = check_meta(str, j);
		if (check == str)
			nstr[i] = ft_strdup(str[j]);
		else
		{
			k = 0;
			while (check[k])
			{
				nstr[i] = ft_strdup(check[k]);
				k++;
				i++;
			}
		}
		free_str(check);
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
	while (nstr[i])
	{
		printf("%s\n", nstr[i]);
		i++;
	}
	return (nstr);
}
