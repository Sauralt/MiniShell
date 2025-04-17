/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:12:45 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/15 13:44:34 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putchar(int fd, int l, char c)
{
	write (fd, &c, 1);
	return (l + 1);
}

static int	ft_putnbr(int fd, int l, int nb)
{
	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return (l + 11);
	}
	if (nb < 0)
	{
		l = ft_putchar (fd, l, '-');
		nb *= -1;
	}
	if (nb >= 10)
		l = ft_putnbr(fd, l, nb / 10);
	l = ft_putchar(fd, l, nb % 10 + '0');
	return (l);
}

int	ft_printint(int fd, int l, int a)
{
	l = ft_putnbr(fd, l, a);
	return (l);
}
/*int	main(void)
{
	int	l = 0;
	l = ft_printint('i', l, -2147483645);
	write(1, "\n", 1);
	printf("%d", l);
	return (0);
}*/
