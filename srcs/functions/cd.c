/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:10:21 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/14 16:05:34 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

const char	*cd_home(const char *path)
{
	const char	*home;

	if (!path || (path[0] == '~' && (path[1] == '/' || path[1] == '\0')))
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_dprintf(2, "cd: HOME not set\n");
			return (NULL);
		}
		return (home);
	}
	return (path);
}

const char	*handle_cd_dash(const char *path, t_shell *data)
{
	char	*oldpwd;

	if (ft_strcmp(path, "-") != 0)
		return (path);
	oldpwd = get_env_value(data->env, "OLDPWD", 6);
	if (!oldpwd || oldpwd[0] == '\0')
	{
		ft_dprintf(2, "cd: OLDPWD not set\n");
		data->exit_code = 1;
		free(oldpwd);
		return (NULL);
	}
	ft_dprintf(1, "%s\n", oldpwd);
	return (oldpwd);
}

void	set_env_var(t_shell *data, const char *key, const char *value)
{
	t_env	*env;
	size_t	key_len;
	char	*new_entry;
	t_env	*new;

	env = data->env;
	key_len = ft_strlen(key);
	new_entry = NULL;
	new_entry = ft_strjoin3(key, "=", value);
	if (set_env_var_loop(env, new_entry, key_len, key) == 1)
		return ;
	new = malloc(sizeof(t_env));
	new->str = new_entry;
	new->prev = NULL;
	new->next = data->env;
	if (data->env)
		data->env->prev = new;
	data->env = new;
}

void	change_directory(const char *path, t_shell *data)
{
	char	current_dir[PATH_SIZE];
	char	*pwd;

	if (!get_current_directory(current_dir, sizeof(current_dir)))
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_code = 1;
	}
	else
	{
		pwd = getenv("PWD");
		if (pwd == NULL)
			pwd = current_dir;
		strncpy(data->prev_dir, pwd, PATH_SIZE - 1);
		data->prev_dir[PATH_SIZE - 1] = '\0';
		if (get_current_directory(current_dir, sizeof(current_dir)))
		{
			set_env_var(data, "PWD", current_dir);
			set_env_var(data, "OLDPWD", data->prev_dir);
		}
		data->exit_code = 0;
	}
}

void	ft_cd(t_shell *data, t_token *str)
{
	char		new_path[PATH_SIZE];
	const char	*resolved_path;

	if (!str || !str->str || !str->str[0])
		resolved_path = cd_home(NULL);
	if (str->str[2] != NULL && str->str[1] != NULL)
	{
		ft_dprintf(2, "cd: too many arguments\n");
		str->exit_code = 1;
		return ;
	}
	else
	{
		resolved_path = cd_home(str->str[1]);
		if (resolved_path)
			resolved_path = handle_cd_dash(resolved_path, data);
	}
	if (!resolved_path)
		return ;
	strncpy(new_path, resolved_path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	change_directory(new_path, data);
	str->exit_code = data->exit_code;
}
