/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/07 13:18:32 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo_n(t_token *str)
{
	int	i;

	i = 1;
	while (str->str[i] && ft_strncmp(str->str[i], "-n", 3) == 0)
		i++;
	if (str->outfile == 1)
	{
		while (str->str[i])
		{
			printf("%s", str->str[i]);
			if (str->str[i + 1])
				printf(" ");
			i++;
		}
	}
	return (0);
}

int	ft_echo(t_token *str)
{
	int	i;
	int	printed;

	i = 1;
	printed = 0;
	while (str->str[i])
	{
		if (ft_strncmp(str->str[i], "-n", 3) == 0)
			return (ft_echo_n(str));
		if (printed)
			ft_dprintf(str->outfile, " ");
		ft_dprintf(str->outfile, "%s", str->str[i]);
		printed = 1;
		i++;
	}
	if (str->outfile == 1)
		printf("\n");
	return (0);
}
