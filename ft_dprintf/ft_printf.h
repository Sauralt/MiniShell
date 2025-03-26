/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:32:15 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/26 17:02:39 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <limits.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdarg.h>

int	ft_dprintf(int fd, const char *f, ...);
int	ft_printchar(int fd, int l, char a);
int	ft_printstring(int fd, int l, char *a);
int	ft_printint(int fd, int l, int a);
int	ft_printhex(int fd, char c, int l, unsigned int a);
int	ft_printptr(int fd, int t, int l, void *a);
int	ft_printuns(int fd, int l, unsigned int a);
#endif
