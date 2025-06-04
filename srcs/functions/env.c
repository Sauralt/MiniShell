/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:16:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/04 19:00:59 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_env(t_shell *data)
{
	t_env	*t;

	t = data->env->next;
	printf("%s\n", data->env->str);
	while (t != data->env)
	{
		printf("%s\n", t->str);
		t = t->next;
	}
	return (0);
}

char	*find_home(void)
{
	char	*home;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	home = getcwd(NULL, 0);
	while (j < 3)
	{
		if (home[i] == '/')
			j++;
		i++;
	}
	temp = ft_strndup(home, 0, i);
	free(home);
	return (temp);
}
