/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/23 17:03:34 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_is_only_n(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_token *str)
{
	int	i;
	int	no_newline;
	int	flag;

	i = 1;
	flag = 0;
	no_newline = 0;
	while (str->str[i] && ft_strncmp(str->str[i], "-n", 2) == 0
		&& ft_str_is_only_n(str->str[i] + 1))
	{
		no_newline = 1;
		flag = 1;
		i++;
	}
	while (str->str[i])
	{
		if (i > 1 && str->str[i - 1] && flag == 0)
			ft_dprintf(str->outfile, " ");
		flag = 0;
		ft_dprintf(str->outfile, "%s", str->str[i]);
		i++;
	}
	if (!no_newline)
		ft_dprintf(str->outfile, "\n");
	return (0);
}
