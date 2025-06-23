/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:09 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/23 14:17:11 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *var_name, size_t var_len)
{
	char	*tmp;
	t_env	*start;

	start = env;
	while (env)
	{
		if (ft_strncmp(env->str, var_name, var_len) == 0
			&& env->str[var_len] == '=')
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
				return (ft_strdup(tmp + 1));
			return (ft_strdup(""));
		}
		env = env->next;
		if (env == start)
			break ;
	}
	return (ft_strdup(""));
}

char	*ft_dollar(t_shell *data, char *str)
{
	char	*res;
	size_t	var_len;

	if (!str || !data)
		return (NULL);
	var_len = ft_strlen(str + 1);
	res = get_env_value(data->env, str + 1, var_len);
	free(str);
	return (res);
}

int	len_var(t_shell *data, char **var)
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
	i = data->start;
	while (i < data->start + data->l)
	{
		len++;
		i++;
	}
	return (len);
}

char	*init_nstr(t_shell *data, char *str, int start, int l)
{
	int		i;
	int		len;
	int		quote;

	i = start - 1;
	len = 0;
	quote = 0;
	if (data->token)
	{
		if (ft_strcmp(data->token->prev->str[0], "<<") == 0)
			return (str);
	}
	while (i++ < start + l)
	{
		quote = quote_flag(quote, str, i);
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '"'
			&& str[i + 1] != '\'' && str[i + 1] != '='
			&& str[i + 1] != '\t'
			&& str[i + 1] != ':' && str[i + 1] != '\0' && quote != 1)
			len++;
	}
	i = data->start;
	if (len > 0)
		return (change_dollar(data, str, len, i));
	return (str);
}
