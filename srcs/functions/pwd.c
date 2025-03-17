/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:22:54 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:22:54 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	ft_pwd(t_shell *data)
{
	char	*pwd;

	if (!data)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		data->exit_code = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	data->exit_code = 0;
}
