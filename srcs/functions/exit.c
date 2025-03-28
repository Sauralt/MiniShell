/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:51:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/26 16:55:25 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	else
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > LONG_MAX / 10
			|| (result == LONG_MAX / 10 && (*str - '0') > LONG_MAX % 10))
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_exit(t_shell *data, t_token *str)
{
	int		has_argument;

	has_argument = (str && str->str && str->str[1]);
	if (has_argument)
	{
		if (!is_numeric(str->str[1]))
		{
			fprintf(stderr, "%s: numeric argument required\n", str->str[0]);
			return (1);
		}
		else
		{
			data->exit_code = ft_atol(str->str[1]);
			if (data->exit_code < 0 || data->exit_code > 255)
				data->exit_code %= 256;
		}
		if (str->str[2])
		{
			fprintf(stderr, "minishell: exit: too many arguments\n");
			return (1);
		}
	}
	printf("exit\n");
	exit((unsigned char)data->exit_code);
}
