/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/24 14:15:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	echo_dollar(t_shell *data, char *str)
{
	t_env	*env;
	char	*tmp;
	int		i;

	i = 0;
	env = data->env;
	while (env->next != data->env)
	{
		if (ft_strncmp(env->str, str + 1, ft_strlen(str + 1)) == 0)
		{
			tmp = ft_strchr(env->str, '=');
			printf("%s ", tmp + 1);
			return (0);
		}
		env = env->next;
	}
	return (0);
}

int	ft_echo(t_shell *data, t_token *str)
{
	t_token	*path;

	path = str;
	while (path->next != str)
	{
		if (path->next->type == 3 && path->next->str[0][1] != '\0')
		{
			echo_dollar(data, path->next->str[0]);
			printf("\n");
			return (0);
		}
		printf("%s ", path->next->str[0]);
		path = path->next;
	}
	// if (str->str[1] && strcmp(str->str[1], "-n") == 0)
	// 	return (0);
	printf("\n");
	return (0);
}
