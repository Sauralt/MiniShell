/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/28 15:17:56 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strdup_param(t_token *t, int i, char **str, int count)
{
	int	j;

	t->str = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (j < count && str[i] != NULL)
	{
		t->str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	t->str[j] = NULL;
}

char	**change_str(t_shell *data, char **str)
{
	t_token	*t;
	int		i;

	t = data->token;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = ft_strdup(t->str[0]);
		i++;
		t = t->next;
	}
	return (str);
}

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
