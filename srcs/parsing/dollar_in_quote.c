/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_in_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:30:47 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/09 17:27:08 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_len(t_shell *data, char **str, int i)
{
	int		len;
	t_shell	*temp;

	temp = data;
	len = 0;
	str = ft_split(str[i], ' ');
	i = 0;
	while (temp->env != data->env->prev)
	{
		i = 0;
		while (str[i])
		{
			if (strncmp(str[i], temp->env->str, ft_strlen(str[i])) == 0)
				len++;
			i++;
		}
		temp->env = temp->env->next;
	}
	i = 0;
	while (str[i])
	{
		if (strncmp(str[i], temp->env->str, ft_strlen(str[i])) == 0)
			len++;
		i++;
	}
	return (len);
}

static int	env_var_len(t_shell *data, int n, char **str)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (str[i][j] != '"' && flag != 2)
	{
		if (str[i][j] == '"')
			flag++;
		if (str[i][j] == '$')
			n += count_env_len(data, str, i);
		j++;
		if (str[i][j] == '\0')
		{
			i++;
			j = 0;
		}
	}
	return (n);
}

static int	check_dollar(char **str, int *i, int *j, int *n)
{
	int	total;

	total = 0;
	(*j)++;
	while (str[(*i)][(*j)] != '"')
	{
		if (str[(*i)][(*j)] == '$')
			total++;
		(*j)++;
		if (str[(*i)][(*j)] == '\0')
		{
			(*i)++;
			(*n)++;
			(*j) = 0;
		}
	}
	return (total);
}

char	**change_env_var(t_shell *data, char **str, char **result, int len)
{
	int		i;
	int		j;
	int		n;
	char	**new_result;

	i = 0;
	n = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
			{
				if (check_dollar(str, &i, &j, &n) != 0)
					n = env_var_len(data, n, str);
			}
			j++;
		}
		i++;
		n++;
	}
	len = 0;
	new_result = malloc(sizeof(char *) * (n + 1));
	if (!new_result)
		return (result);
	new_result = change_result(data, result, new_result);
	return (new_result);
}
