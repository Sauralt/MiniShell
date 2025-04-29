/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:54 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/29 12:59:09 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_pwd(t_shell *data)
{
	char	*pwd;

	if (!data)
		return (1);
	if (data->token != data->token->next)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		data->exit_code = 1;
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	data->exit_code = 0;
	return (0);
}
