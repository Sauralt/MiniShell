/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:13:20 by cfleuret          #+#    #+#             */
/*   Updated: 2025/02/11 16:28:07 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(int fd, int l, char c)
{
	write (fd, &c, 1);
	return (l + 1);
}

int	ft_printuns(int fd, int l, unsigned int a)
{
	if (a >= 10)
		l = ft_printuns(fd, l, a / 10);
	l = ft_putchar(fd, l, a % 10 + '0');
	return (l);
}
/*int	main(void)
{
	int	l = 0;
	l = ft_printuns(l, 4);
	write(1, "\n", 1);
	printf("%d", l);
	return (0);
}*/
