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

void	ft_cd(char *path)
{
	static char	prev_dir[1024] = "";
	char		current_dir[1024];

	if (!path)
		return ;
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (strcmp(path, "..") == 0)
	{
		if (prev_dir[0] == '\0')
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return ;
		}
		path = prev_dir;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
	}
	else
	{
		strncpy(prev_dir, current_dir, sizeof(prev_dir) - 1);
		prev_dir[sizeof(prev_dir) - 1] = '\0';
		if (getcwd(current_dir, sizeof(current_dir)) != NULL)
			setenv("PWD", current_dir, 1);
	}
}
