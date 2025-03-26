/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/26 14:32:42 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	echo_dollar(t_shell *data, char *str)
{
	t_env	*env;
	char	*tmp;
	t_env	*start;

	env = data->env;
	if (!env)
		return (0);
	start = env;
	while (env)
	{
		if (ft_strncmp(env->str, str + 1, ft_strlen(str + 1)) == 0)
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
				printf(" %s", tmp + 1);
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
	t_token		*path;
	int			printed;

	printed = 0;
	path = str->next;
	while (path != str)
	{
		if (path->type == 3 && path->str[0][1] != '\0')
			printed += echo_dollar(data, path->str[0]);
		else
		{
			if (printed)
				printf(" ");
			printf("%s", path->str[0]);
			printed = 1;
		}
		path = path->next;
	}
	printf("\n");
	return (0);
}
