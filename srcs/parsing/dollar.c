/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:09 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/22 17:18:21 by cfleuret         ###   ########.fr       */
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

static int	len_var(t_shell *data, char **var)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	printf("%d\n", data->del_num);
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
	i = data->start;
	while (i < data->start + data->l)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*change_str(char *str, char **var, t_shell *data, int j)
{
	char	*nstr;
	int		i;
	int		t;
	int		k;

	nstr = malloc(sizeof(char) * (len_var(data, var) + 1));
	i = data->start;
	j = 0;
	t = 0;
	while (i < data->start + data->l)
	{
		k = 0;
		if (str[i] == '$')
		{
			while (i < data->start + data->l && ((str[i] >= 'A' && str[i] <= 'Z')
					|| str[i] == '$' || ft_isdigit(str[i]) || str[i] == '_'))
				i++;
			while (var[j][k])
			{
				nstr[t] = var[j][k];
				t++;
				k++;
			}
			j++;
		}
		else
		{
			nstr[t] = str[i];
			t++;
			i++;
		}
	}
	nstr[t] = '\0';
	free_str(var);
	return (nstr);
}

static char	*change_dollar(t_shell *data, char *str, int len, int i)
{
	int		j;
	int		start;
	int		quote;
	char	**var;
	char	*temp;

	var = malloc(sizeof(char *) * (len + 1));
	if (!var)
		return (NULL);
	j = 0;
	quote = 0;
	while (i < data->start + data->l)
	{
		if (str[i] == '\'' && quote == 0)
			quote = 1;
		else if (str[i] == '\'' && quote == 1)
			quote = 0;
		if (str[i] == '$' && quote != 1)
		{
			start = i;
			while (i < data->start + data->l && ((str[i] >= 'A' && str[i] <= 'Z')
					|| str[i] == '$' || ft_isdigit(str[i]) || str[i] == '_'))
				i++;
			temp = ft_strndup(str, start, i - start);
			var[j] = ft_dollar(data, temp);
			j++;
			i--;
		}
		i++;
	}
	var[j] = NULL;
	str = change_str(str, var, data, j);
	return (str);
}

char	*init_nstr(t_shell *data, char *str, int start, int l)
{
	int		i;
	int		len;
	int		quote;

	i = 0;
	i += start;
	len = 0;
	quote = 1;
	while (i < start + l)
	{
		if (str[i] == '\'')
			quote = 0;
		if (str[i] == '$' && quote != 0)
			len++;
		i++;
	}
	i = data->start;
	data->start = start;
	data->l = l;
	if (len > 0)
		str = change_dollar(data, str, len, i);
	return (str);
}
