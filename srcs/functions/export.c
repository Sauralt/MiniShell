/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:22:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:22:49 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	print_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("declare -x %s\n", environ[i]);
		i++;
	}
}


int	ft_export(char *arg)
{
	char		*key;
	char		*value;
	char		*delim;
	extern char	**environ;
	int			env_count;
	size_t 		len;
	int			i;
	char 		**new_env;

	len = ft_strlen(key);
	env_count = 0;
	delim = ft_strchr(arg, '=');
	if (!delim || delim == arg)
	{
		fprintf(stderr, "Erreur : Format attendu 'clé=valeur'\n");
		return (1);
	}
	key = strndup(arg, delim - arg);
	value = ft_strdup(delim + 1);
	if (!key || !value)
	{
		perror("strdup");
		return (1);
	}
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], key, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			environ[i] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
			if (!environ[i])
			{
				perror("malloc");
				free(key);
				free(value);
				return (1);
			}
			sprintf(environ[i], "%s=%s", key, value);
			free(key);
			free(value);
			return (0);
		}
		i++;
	}
	while (environ[env_count])
		env_count++;
	new_env = malloc((env_count + 2) * sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		free(key);
		free(value);
		return (1);
	}
	i = 0;
	while (i < env_count)
	{
		new_env[i] = environ[i];
		i++;
	}
	new_env[env_count] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!new_env[env_count])
	{
		perror("malloc");
		free(key);
		free(value);
		free(new_env);
		return (1);
	}
	sprintf(new_env[env_count], "%s=%s", key, value);
	new_env[env_count + 1] = NULL;
	environ = new_env;
	free(key);
	free(value);
	return (0);
}
