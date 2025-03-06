/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:55:25 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/06 12:25:48 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	error(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	exit(EXIT_FAILURE);
}

char	*find_absolute(char *cmd)
{
	int		i;
	int		j;
	char	*ncmd;

	i = ft_strlen(cmd);
	while (cmd[i] != '/' && i != 0)
		i--;
	if (i == 0)
		return (cmd);
	ncmd = malloc(sizeof(char) * (ft_strlen(cmd) - i + 1));
	j = 0;
	while (cmd[i])
	{
		ncmd[j] = cmd[i];
		i++;
		j++;
	}
	ncmd[j] = '\0';
	free(cmd);
	return (ncmd);
}
