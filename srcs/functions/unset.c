/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:22:58 by mgarsaul         ###   ########.fr       */
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
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unset(t_shell *data, char *cmd)
{
	extern char	**environ;
	int			index;

	(void)data;
	if (!cmd || ft_strchr(cmd, '='))
	{
		fprintf(stderr, "unset: `%s': not a valid identifier\n", cmd);
		data->exit_code = 1;
		return (1);
	}
	index = find_env_index(cmd);
	if (index == -1)
	{
		data->exit_code = 0;
		return (1);
	}
	free(environ[index]);
	while (environ[index])
	{
		environ[index] = environ[index + 1];
		index++;
	}
	data->exit_code = 0;
	return (0);
}
