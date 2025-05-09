/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:51:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/09 16:04:47 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_exit(t_token *str)
{
	int	has_arg;

	has_arg = (str && str->str && str->str[1]);
	printf("exit\n");
	if (has_arg)
	{
		if (!is_numeric(str->str[1]))
		{
			ft_dprintf(2, "exit: %s: numeric argument required\n", str->str[1]);
			exit(2);
		}
		if (str->str[2])
		{
			ft_dprintf(2, "minishell: exit: too many arguments\n");
			str->exit_code = 1;
			return (1);
		}
		str->exit_code = ft_atol(str->str[1]);
	}
	exit((unsigned char)str->exit_code);
}
