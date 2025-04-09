/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dollar_in_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:02 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/09 17:40:01 by cfleuret         ###   ########.fr       */
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

static int	is_valid_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| (c == '_'));
}

static int	check_var_exist(t_shell *data, char *str, int j)
{
	t_env	*env;
	char	*temp;
	int		start;
	int		len;
	int		result;

	start = j;
	env = data->env;
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
	result = len_var(temp, env);
	free(temp);
	return (result);
}

// static char	*make_str(int len, char *str, t_shell *data)
// {
// 	char	*new_str;
// 	char	*temp;
// 	int		i;
// 	int		k;
// 	int		j;

// 	i = 0;
// 	k = 0;
// 	new_str = malloc(sizeof(char) * (len + 1));
// 	if (!new_str)
// 		return (NULL);

// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			i++;
// 			temp = dollar_utils_1(data, str, i);
// 			if (temp)
// 			{
// 				j = 0;
// 				while (temp[j])
// 					new_str[k++] = temp[j++];
// 				free(temp);
// 			}
// 			while (str[i] && is_valid_var_char(str[i]))
// 				i++;
// 		}
// 		else
// 			new_str[k++] = str[i++];
// 	}
// 	new_str[k] = '\0';
// 	return (new_str);
// }

static char	*make_str(int len, char *str, t_shell *data)
{
	char	*new_str;
	char	*temp;
	int		i;
	int		k;
	int		j;

	i = 0;
	k = 0;
	new_str = malloc(sizeof(char) * (len + 1));
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
	int	j;
	int	k;
	int	len;

	j = 0;
	len = 0;
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
	new_result[i] = make_str(len, str, data);
	i++;
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
	new_result[i] = NULL;
	return (new_result);
}
