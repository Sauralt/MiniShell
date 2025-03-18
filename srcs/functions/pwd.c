/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:54 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/18 16:22:30 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_pwd(t_shell *data)
{
	char	*pwd;

	if (!data)
		return (1);
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
