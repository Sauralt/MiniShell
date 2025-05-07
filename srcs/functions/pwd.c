/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:54 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/05 14:45:07 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	ft_pwd(t_shell *data, t_token *t)
{
	char	*pwd;

	if (!data)
		return (1);
	if (t->str[1] && t->str[1][0] == '-')
	{
		data->exit_code = 2;
		ft_dprintf(2, "%s: %s: invalid option\n", t->str[0], t->str[1]);
		return (1);
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
