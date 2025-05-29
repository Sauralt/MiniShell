/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:51:51 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/29 18:58:47 by cfleuret         ###   ########.fr       */
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

static int	compare_abs_str(const char *a, const char *b)
{
	size_t len_a;
	size_t len_b;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a != len_b)
		return (len_a > len_b);
	return (ft_strcmp(a, b) > 0);
}

static int	is_numeric(const char *str)
{
	int			sign;
	const char *start;
	const char *limit;

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
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (0);
	if (start == str)
		return (1);
	limit = (sign == 1)
		? "9223372036854775807"
		: "9223372036854775808";
	if (compare_abs_str(start, limit))
		return (0);
	return (1);
}

static long long	ft_atol(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
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
			str->exit_code = 1;
			return (ft_dprintf(2, "minishell: exit: too many arguments\n"), 1);
		}
		str->exit_code = (unsigned char)ft_atol(str->str[1]);
	}
	if (data->exit_code == 0)
		has_arg = str->exit_code;
	else
		has_arg = data->exit_code;
	free_exit(data);
	exit(has_arg);
}
