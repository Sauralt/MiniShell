/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:51:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/27 14:37:05 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_exit(t_shell *data)
{
	free_tokens(data->token);
	free_env(data->env);
	free(data);
	rl_clear_history();
}

static int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (ft_strcmp(str, "9223372036854775808") == 0
		|| ft_strcmp(str, "-9223372036854775809") == 0)
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

static long long	ft_atol(const char *str)
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

int	ft_exit(t_shell *data, t_token *str)
{
	int	has_arg;

	has_arg = (str && str->str && str->str[1]);
	printf("exit\n");
	if (has_arg)
	{
		if (!is_numeric(str->str[1]))
		{
			ft_dprintf(2, "exit: %s: numeric argument required\n", str->str[1]);
			free_exit(data);
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
	has_arg = str->exit_code;
	free_exit(data);
	exit(has_arg);
}
