/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_str_verif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:09 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/31 16:11:45 by mgarsaul         ###   ########.fr       */
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
	if (!env || !str || str[0] != '$' || !str[1])
		return (ft_strdup(str));
	start = env;
	var_len = ft_strlen(str + 1);
	while (env)
	{
		if (ft_strncmp(env->str, str + 1, var_len) == 0
			&& env->str[var_len] == '=')
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
				return (str = ft_strdup(tmp + 1));
		}
		env = env->next;
		if (env == start)
			break ;
	}
	free(str);
	return (ft_strdup(""));
}

char	*ft_quote(t_shell *data, char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;
	char	*tmp;

	if (!str)
		return (NULL);

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			j = i;
			while (str[j] && str[j] != quote)
				j++;
			if (!str[j])
			{
				if (quote == '"')
					ft_dprintf(2, "open quote\n");
				else
					ft_dprintf(2, "open dquote\n");
				return (ft_strdup(""));
			}
			tmp = ft_substr(str, i, j - i);
			if (quote == '\'')
				tmp = ft_dollar(data, str);
			result = ft_strjoin(result, tmp);
			i = j + 1;
		}
		else
		{
			j = i;
			while (str[j] && str[j] != '\'' && str[j] != '"')
				j++;
			tmp = ft_substr(str, i, j - i);
			result = ft_strjoin(result, tmp);
			i = j;
		}
	}
	return (result);
}


char	*ft_verif_str_type(t_shell *data, char *str)
{
	if (!str)
		return (NULL);
	str = ft_quote(data, str);
	str = ft_dollar(data, str);
	return (str);
}
