/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:10:21 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/05 17:11:03 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

// char	*cd_home(char *path, t_shell *data)
// {
// 	char	*home;
// 	char	*expanded;
// 	int		home_from_find;
// 	char	*result;

// 	home_from_find = 0;
// 	if (!path || (path[0] == '~' && (path[1] == '/' || path[1] == '\0')))
// 	{
// 		home = getenv("HOME");
// 		if (!home && path && path[0] == '~')
// 		{
// 			home = find_home();
// 			home_from_find = 1;
// 		}
// 		if (!home)
// 		{
// 			ft_dprintf(2, "cd: HOME not set\n");
// 			data->exit_code = 1;
// 			return (NULL);
// 		}
// 		if (!path || path[1] == '\0')
// 		{
// 			result = ft_strdup(home);
// 			if (home_from_find)
// 				free(home);
// 			return (result);
// 		}
// 		expanded = ft_strjoin(home, path + 1);
// 		if (home_from_find)
// 			free(home);
// 		return (expanded);
// 	}
// 	return (ft_strdup(path));
// }

static char	*resolve_home_path(char *path, t_shell *data)
{
	char	*home;
	int		home_from_find;
	char	*result;

	home_from_find = 0;
	home = getenv("HOME");
	if (!home && path && path[0] == '~')
	{
		home = find_home();
		home_from_find = 1;
	}
	if (!home)
	{
		ft_dprintf(2, "cd: HOME not set\n");
		data->exit_code = 1;
		return (NULL);
	}
	if (!path || path[1] == '\0')
		result = ft_strdup(home);
	else
		result = ft_strjoin(home, path + 1);
	if (home_from_find)
		free(home);
	return (result);
}

char	*cd_home(char *path, t_shell *data)
{
	if (!path || (path[0] == '~' && (path[1] == '/' || path[1] == '\0')))
		return (resolve_home_path(path, data));
	return (ft_strdup(path));
}


static void	set_env_var(t_shell *data, const char *key, const char *value)
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

static void	change_directory(char *path, t_shell *data)
{
	char	old_dir[PATH_SIZE];
	char	new_dir[PATH_SIZE];

	if (!get_current_directory(data->env, old_dir, sizeof(old_dir)))
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_code = 1;
		return ;
	}
	if (!get_current_directory(data->env, new_dir, sizeof(new_dir)))
	{
		perror("cd: getcwd (after chdir)");
		data->exit_code = 1;
		return ;
	}
	set_env_var(data, "OLDPWD", old_dir);
	set_env_var(data, "PWD", new_dir);
	ft_strncpy(data->prev_dir, old_dir, PATH_SIZE - 1);
	data->prev_dir[PATH_SIZE - 1] = '\0';
	data->exit_code = 0;
}

void	ft_cd(t_shell *data, t_token *t)
{
	char	new_path[PATH_SIZE];
	char	*path;

	if (ft_check_oldpwd(data->env) == 1)
		ft_add_stack(&data->env, ft_new_stack("OLDPWD="));
	if (!t || !t->str || !t->str[0])
		path = cd_home(NULL, data);
	if (t->str[1] != NULL && t->str[2] != NULL)
	{
		ft_dprintf(2, "cd: too many arguments\n");
		t->exit_code = 1;
		return ;
	}
	else
		path = cd_home(t->str[1], data);
	t->exit_code = data->exit_code;
	if (!path)
		return ;
	ft_strncpy(new_path, path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	free(path);
	change_directory(new_path, data);
	t->exit_code = data->exit_code;
}
