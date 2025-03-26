/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/26 16:03:40 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	echo_dollar(t_shell *data, char *str)
{
	t_env	*env;
	char	*tmp;
	t_env	*start;
	size_t	var_len;

	env = data->env;
	if (!env || !str || str[0] != '$' || !str[1])
		return (0);
	start = env;
	var_len = ft_strlen(str + 1);
	while (env)
	{
		if (ft_strncmp(env->str, str + 1, var_len)
			== 0 && env->str[var_len] == '=')
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
				printf("%s ", tmp + 1);
			return (1);
		}
		env = env->next;
		if (env == start)
			break ;
	}
	return (0);
}

int	ft_echo(t_shell *data, t_token *str)
{
	int		printed;
	int		i;

	i = 1;
	printed = 0;
	while (str->str[i])
	{
		if (str->str[i] && str->str[i][0] == '$')
			printed += echo_dollar(data, str->str[i]);
		else
		{
			if (str->str && str->str[i])
				printf("%s ", str->str[i]);
			printed = 1;
		}
		i++;
	}
	printf("\n");
	return (0);
}
