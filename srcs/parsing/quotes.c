/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:19:33 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/22 13:58:01 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_quote(char **str, char c, int i, int j)
{
	char	*result;
	int		k;

	k = 0;
	result = str_quote_init(str, c, i, &j);
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == c)
			{
				result[k] = '\0';
				return (result);
			}
			result[k++] = str[i][j++];
		}
		i++;
		j = 0;
		if (str[i])
			result[k++] = ' ';
	}
	free(result);
	return (NULL);
}

static int	change_str_quote_loop(char **result, char **str, int *i, int k)
{
	while (str[*i] && (str[*i][0] != '\'' && str[*i][0] != '"'))
	{
		result[k++] = ft_strdup(str[*i]);
		(*i)++;
	}
	return (k);
}

static char	**change_str_quote(char **result, char **str, int i, int j)
{
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
			if (new_i < 0)
				return (NULL);
			i = new_i + 1;
		}
		k = change_str_quote_loop(result, str, &i, k);
	}
	result[k] = NULL;
	return (result);
}

static int	ft_quote_loop(char **str, int i, int j, int n)
{
	int	new_i;

	new_i = 0;
	while (str[i][j])
	{
		if (str[i][j] == '\'' || str[i][j] == '"')
		{
			if (new_i == 0)
			{
				new_i = skip(str, str[i][j], i, j);
				i = new_i;
				if (new_i < 0)
					return (-1);
				j = change_j(str, str[i][j], i, j) - 1;
				n++;
			}
		}
		j++;
	}
	return (i);
}

char	**ft_quote(char **str, t_shell *data)
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
		if (i != ft_quote_loop(str, i, j, n))
			i = ft_quote_loop(str, i, j, n);
		if (i == -1)
			return (NULL);
		n++;
		i++;
	}
	result = malloc(sizeof(char *) * (n + 1));
	if (!result)
		return (NULL);
	result = change_str_quote(result, str, i, j);
	result = change_env_var(data, str, result);
	free_str(str);
	return (result);
}