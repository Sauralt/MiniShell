/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:10:21 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:10:21 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	ft_cd(char **cmd)
{
	if (cmd[1] == NULL)
	{
		if (chdir(getenv("HOME")) == -1)
			perror("minishell");
	}
	else if (chdir(cmd[1]) == -1)
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
}
