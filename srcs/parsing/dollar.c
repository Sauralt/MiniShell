/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:09 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/16 14:25:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dollar(t_shell *data, char *str)
{
	t_env	*env;
	char	*tmp;
	t_env	*start;
	size_t	var_len;

	env = data->env;
	start = env;
	var_len = ft_strlen(str + 1);
	while (env)
	{
		if (ft_strncmp(env->str, str + 1, var_len) == 0
			&& env->str[var_len] == '=')
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
			{
				free(str);
				return (ft_strdup(tmp + 1));
			}
		}
		env = env->next;
		if (env == start)
			break ;
	}
	free(str);
	return (ft_strdup(""));
}

static int	len_var(char **var, char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (var[i])
	{
		j = 0;
		while (var[i][j])
		{
			j++;
			len++;
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		len++;
		i++;
	}
	return (len);
}

static char	*change_str(char *str, char **var, int i, int j)
{
	char	*nstr;
	int		l;
	int		k;

	nstr = malloc(sizeof(char) * (len_var(var, str) + 1));
	i = 0;
	j = 0;
	l = 0;
	while (str[i])
	{
		k = 0;
		if (str[i] == '$')
		{
			while (str[i] && ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '$'
					|| ft_isdigit(str[i]) || str[i] == '_'))
				i++;
			while (var[j][k])
			{
				nstr[l] = var[j][k];
				l++;
				k++;
			}
			j++;
		}
		else
		{
			nstr[l] = str[i];
			l++;
			i++;
		}
	}
	nstr[l] = '\0';
	free_str(var);
	return (nstr);
}

static char	*change_dollar(t_shell *data, char *str, int len, int i)
{
	int		j;
	int		start;
	char	**var;
	char	*temp;

	var = malloc(sizeof(char *) * (len + 1));
	if (!var)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			while (str[i] && ((str[i] >= 'A' && str[i] <= 'Z') || str[i] == '$'
				|| ft_isdigit(str[i]) || str[i] == '_'))
				i++;
			temp = ft_strndup(str, start, i - start);
			var[j] = ft_dollar(data, temp);
			j++;
			i--;
		}
		i++;
	}
	var[j] = NULL;
	str = change_str(str, var, i, j);
	return (str);
}

char	*init_nstr(t_shell *data, char *str, int flag)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (flag == 0)
		return (str);
	else
	{
		while (str[i])
		{
			if (str[i] == '$')
				len++;
			i++;
		}
		i = 0;
		if (len > 0)
			str = change_dollar(data, str, len, i);
		return (str);
	}
}
