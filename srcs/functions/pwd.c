/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:54 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/27 13:49:43 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_pwd(t_shell *data, t_token *t)
{
	t_env	*env;
	char	*temp;

	if (!data)
		return (1);
	if (t->str[1] && t->str[1][0] == '-')
	{
		data->exit_code = 2;
		ft_dprintf(2, "%s: %s: invalid option\n", t->str[0], t->str[1]);
		return (1);
	}
	env = data->env;
	if (!env)
	{
		perror("getcwd");
		data->exit_code = 1;
		return (1);
	}
	while (ft_strncmp("PWD=", env->str, 4) != 0)
		env = env->next;
	temp = ft_strndup(env->str, 4, ft_strlen(env->str) - 4);
	printf("%s\n", temp);
	free(temp);
	data->exit_code = 0;
	return (0);
}
