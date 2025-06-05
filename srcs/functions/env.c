/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:16:49 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/05 15:19:41 by mgarsaul         ###   ########.fr       */
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
	char	*cwd;
	int		slash_count;
	int		i;

	i = 0;
	slash_count = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	while (cwd[i])
	{
		if (cwd[i] == '/')
			slash_count++;
		if (slash_count == 3)
			break ;
		i++;
	}
	if (slash_count < 3)
	{
		return (cwd);
	}
	cwd[i + 1] = '\0';
	return (cwd);
}
