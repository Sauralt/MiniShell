/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_in_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:02 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/15 15:31:43 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_var(char *str, t_env *env)
{
	t_env	*t;
	int		key_len;
	int		i;

	key_len = ft_strlen(str);
	t = env;
	while (t)
	{
		i = 0;
		while (t->str[i] && t->str[i] != '=')
			i++;
		if (i == key_len && strncmp(t->str, str, key_len) == 0
			&& t->str[i] == '=')
			return (ft_strlen(&t->str[i + 1]));
		t = t->next;
		if (t == env)
			break ;
	}
	return (0);
}

static int	check_var_exist(t_shell *data, char *str, int j)
{
	char	*temp;
	int		start;
	int		len;
	int		result;

	start = j;
	while (str[j] && is_valid_var_char(str[j]))
		j++;
	len = j - start;
	if (len == 0)
		return (0);
	temp = malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	strncpy(temp, &str[start], len);
	temp[len] = '\0';
	result = len_var(temp, data->env);
	free(temp);
	return (result);
}

static char	*make_str(int len, char *str, t_shell *data)
{
	char	*new_str;
	char	*temp;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	new_str = malloc(sizeof(char) * (len + 100));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			temp = dollar_utils_1(data, str, i);
			if (temp)
			{
				j = 0;
				while (temp[j] && k < len)
					new_str[k++] = temp[j++];
				free(temp);
			}
			while (str[i] && is_valid_var_char(str[i]))
				i++;
		}
		else if (k < len)
			new_str[k++] = str[i++];
		else
			break ;
	}
	new_str[k] = '\0';
	return (new_str);
}

static void	make_new_str(char **new_result, char *str, t_shell *data, int i)
{
	int		len;
	int		j;
	int		var_len;

	len = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '$')
		{
			j++;
			var_len = check_var_exist(data, str, j);
			len += var_len;
			while (str[j] && is_valid_var_char(str[j]))
				j++;
		}
		else
		{
			len++;
			j++;
		}
	}
	new_result[i] = make_str(len, str, data);
}


char	**change_result(t_shell *data, char **result, char **new_result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (result[j])
	{
		if (check_str(result[j]) == 0)
			new_result[i] = ft_strdup(result[j]);
		else
			make_new_str(new_result, result[j], data, i);
		i++;
		j++;
	}
	free_str(result);
	new_result[i] = NULL;
	return (new_result);
}
