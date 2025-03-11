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

int	get_current_directory(char *buffer, size_t size)
{
	if (getcwd(buffer, size) == NULL)
	{
		perror("getcwd");
		return (0);
	}
	return (1);
}

const char	*handle_cd_dash(const char *path, char *prev_dir)
{
	if (strcmp(path, "..") == 0)
	{
		if (prev_dir[0] == '\0')
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (NULL);
		}
		return (prev_dir);
	}
	return (path);
}

void	change_directory(const char *path, char *prev_dir)
{
	char	current_dir[PATH_SIZE];

	if (!get_current_directory(current_dir, sizeof(current_dir)))
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
	}
	else
	{
		strncpy(prev_dir, current_dir, sizeof(current_dir) - 1);
		prev_dir[sizeof(current_dir) - 1] = '\0';
		if (get_current_directory(current_dir, sizeof(current_dir)))
			setenv("PWD", current_dir, 1);
	}
}

void	ft_cd(char *path)
{
	static char		prev_dir[PATH_SIZE] = "";
	char			new_path[PATH_SIZE];
	const char		*resolved_path;

	if (!path)
		return ;
	resolved_path = handle_cd_dash(path, prev_dir);
	if (!resolved_path)
		return ;
	strncpy(new_path, resolved_path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	change_directory(new_path, prev_dir);
}
