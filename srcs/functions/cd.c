/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:10:21 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/27 14:27:56 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*cd_home(char *path)
{
	char	*home;

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

char	*handle_cd_dash(char *path, t_shell *data)
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

	if (!get_current_directory(old_dir, sizeof(old_dir)))
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		data->exit_code = 1;
		return ;
	}
	if (!get_current_directory(new_dir, sizeof(new_dir)))
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
	char	*resolved_path;

	if (data->env->next == data->env)
		ft_add_stack(&data->env,
			ft_new_stack(ft_strjoin("OLD", data->env->str)));
	if (!t || !t->str || !t->str[0])
		resolved_path = cd_home(NULL);
	if (t->str[1] != NULL && t->str[2] != NULL)
	{
		ft_dprintf(2, "cd: too many arguments\n");
		t->exit_code = 1;
		return ;
	}
	else
		resolved_path = init_resolved_path(data, t, resolved_path);
	if (!resolved_path)
		return ;
	ft_strncpy(new_path, resolved_path, PATH_SIZE - 1);
	new_path[PATH_SIZE - 1] = '\0';
	if (t->str[1] && t->str[1][0] != '~'
		&& ft_strcmp(resolved_path, t->str[1]) != 0)
		free(resolved_path);
	change_directory(new_path, data);
	t->exit_code = data->exit_code;
}
