/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/18 16:25:49 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	find_env_index(const char *key)
{
	extern char	**environ;
	size_t		len;
	int			i;

	i = 0;
	len = ft_strlen(key);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], key, len) == 0 && environ[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}


int	ft_unset(char **cmd)
{
	int			i;
	extern char	**environ;
	int			index;

	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
		{
			printf("unset: invalid identifier\n");
			return (1);
		}

		index = find_env_index(cmd[i]);
		if (index != -1)
		{
			free(environ[index]);
			while (environ[index])
			{
				environ[index] = environ[index + 1];
				index++;
			}
		}
		i++;
	}
	return (0);
}