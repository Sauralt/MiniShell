/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:51:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/06/23 14:14:41 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	compare_abs_str(const char *a, const char *b)
{
	size_t	len_a;
	size_t	len_b;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a != len_b)
		return (len_a > len_b);
	return (ft_strcmp(a, b) > 0);
}

static int	is_numeric(const char *str)
{
	int			sign;
	const char	*start;

	sign = 1;
	if (!str || !*str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		return (0);
	while (*str == '0')
		str++;
	start = str;
	return (check_numeric(start, str, sign));
}

static long long	ft_atol(const char *str)
{
	long long	result;
	int			sign;

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

static int	handle_exit_args(t_shell *data, t_token *str, int flag)
{
	if (!is_numeric(str->str[1]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", str->str[1]);
		free_exit(data, flag);
		exit(2);
	}
	if (str->str[2])
	{
		str->exit_code = 1;
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		return (1);
	}
	str->exit_code = (unsigned char)ft_atol(str->str[1]);
	return (0);
}

int	ft_exit(t_shell *data, t_token *str, int flag)
{
	int	has_arg;

	if (flag == 0)
		printf("exit\n");
	if (flag == 0)
		flag = -1;
	has_arg = (str && str->str && str->str[1]);
	if (has_arg)
	{
		if (handle_exit_args(data, str, flag))
			return (1);
	}
	if (data->exit_code == 0)
		has_arg = str->exit_code;
	else
		has_arg = data->exit_code;
	free_exit(data, flag);
	exit(has_arg);
}
