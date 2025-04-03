/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:13:26 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/03 16:31:06 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *str)
{
	int	i;
	int	printed;

	i = 1;
	printed = 0;
	while (str->str[i])
	{
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
