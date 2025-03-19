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

void	change_directory(const char *path, t_shell *data)
{
	char	current_dir[PATH_SIZE];

	if (!get_current_directory(current_dir, sizeof(current_dir)))
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_code = 1;
	}
	else
	{
		strncpy(data->prev_dir, current_dir, PATH_SIZE - 1);
		data->prev_dir[PATH_SIZE - 1] = '\0';
		if (get_current_directory(current_dir, sizeof(current_dir)))
		{
			setenv("PWD", current_dir, 1);
			setenv("OLDPWD", data->prev_dir, 1);
		}
		data->exit_code = 0;
	}
}

int	ft_cd(t_shell *data, char *path)
{
	char	new_path[PATH_SIZE];

	if (!path)
	{
		data->exit_code = 0;
		return (1);
	}
	strncpy(new_path, path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	change_directory(new_path, data);
	return (0);
}
