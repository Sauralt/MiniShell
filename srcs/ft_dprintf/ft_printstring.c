/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:58:18 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/15 13:44:40 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_printstring(int fd, int l, char *a)
{
	int	i;

	if (a == NULL)
	{
		write (fd, "(null)", 6);
		return (l + 6);
	}
	i = 0;
	while (a[i])
	{
		write(fd, &a[i], 1);
		i++;
	}
	l += i;
	return (l);
}
/*int	main(void)
{
	int l = 0;
	l = ft_printstring(l, "abc");
	printf("%d", l);
	return (0);
}*/
