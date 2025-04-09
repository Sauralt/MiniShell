/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_in_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:02 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/09 13:39:16 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_str(char *str)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == '$')
			total++;
		i++;
	}
	return (total);
}

static int	len_var(char *str, t_env *env)
{
	t_env	*t;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	t = env;
	while (t != env->prev)
	{
		if (strncmp(t->str, str, ft_strlen(str)) == 0)
		{
			while (t->str[i] != '=')
				i++;
			i++;
			while (t->str[i])
			{
				i++;
				j++;
			}
			return (j);
		}
		t = t->next;
	}
	if (strncmp(t->str, str, ft_strlen(str)) == 0)
	{
		while (t->str[i] != '=')
			i++;
		i++;
		while (t->str[i])
		{
			i++;
			j++;
		}
		return (j);
	}
	return (0);
}

static int	check_var_exist(t_shell *data, char *str, int j)
{
	t_env	*env;
	char	*temp;
	int		i;
	int		t;

	i = 0;
	t = j;
	env = data->env;
	while (str[t] < 'A' || str[t] > 'Z')
	{
		i++;
		t++;
	}
	temp = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[j] < 'A' || str[j] > 'Z')
	{
		temp[i] = str[j];
		t++;
		i++;
	}
	temp[i] = '\0';
	i = len_var(temp, data->env);
	free(temp);
	return (i);
}

static char	make_str(int len, char *str, t_env *env)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (len + 1));
	i = 0;
}

static void	make_new_str(char **new_result, char *str, t_shell *data, int i)
{
	int	j;
	int	k;
	int	len;

	j = 0;
	k = check_str(str);
	while (k != 0)
	{
		while (str[j])
		{
			if (str[j] != '$')
				len++;
			else
			{
				len += check_var_exist(data, str, j);
				while (str[j] < 'A' || str[j] > 'Z')
					j++;
				j--;
				k--;
			}
			j++;
		}
	}
	new_result[i] = make_str(len, str, data->env);
	i++;
}

char	**change_result(t_shell *data, char **result, char **new_result)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (new_result[i])
	{
		if (check_str(result[j]) == 0)
			new_result[i] = ft_strdup(result[j]);
		else
			make_new_str(new_result, result[j], data, i);
	}
}
