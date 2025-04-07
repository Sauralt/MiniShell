/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:10:21 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/07 13:22:05 by mgarsaul         ###   ########.fr       */
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

const char	*cd_home(const char *path)
{
	const char	*home;

	if (!path || (path[0] == '~' && (path[1] == '/' || path[1] == '\0')))
	{
		home = getenv("HOME");
		if (!home)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (NULL);
		}
		return (home);
	}
	return (path);
}

const char	*handle_cd_dash(const char *path)
{
	if (ft_strncmp(path, "-", 1) == 0)
		return ("..");
	return (path);
}

int	change_directory(const char *path, t_shell *data)
{
	char	current_dir[PATH_SIZE];
	char	*pwd;

	if (!get_current_directory(current_dir, sizeof(current_dir)))
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	pwd = getenv("PWD");
	if (pwd == NULL)
		pwd = current_dir;
	strncpy(data->prev_dir, pwd, PATH_SIZE - 1);
	data->prev_dir[PATH_SIZE - 1] = '\0';
	if (get_current_directory(current_dir, sizeof(current_dir)))
	{
		setenv("PWD", current_dir, 1);
		setenv("OLDPWD", data->prev_dir, 1);
	}
	return (0);
}

int	ft_cd(t_shell *data, t_token *str)
{
	char		new_path[PATH_SIZE];
	const char	*resolved_path;

	if (!str || !str->str || !str->str[0])
		resolved_path = cd_home(NULL);
	else
	{
		resolved_path = cd_home(str->str[1]);
		if (resolved_path)
			resolved_path = handle_cd_dash(resolved_path);
	}
	if (!resolved_path)
		return (1);
	strncpy(new_path, resolved_path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	return (change_directory(new_path, data));
}
