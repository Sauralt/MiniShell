/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-10 14:01:42 by mgarsaul          #+#    #+#             */
/*   Updated: 2025-03-10 14:01:42 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

bool	is_builtin(char *line)
{
	if (ft_strcmp(line, "echo") == 0 || ft_strcmp(line, "cd") == 0
		|| ft_strcmp(line, "pwd") == 0 || ft_strcmp(line, "export") == 0
		|| ft_strcmp(line, "unset") == 0 || ft_strcmp(line, "env") == 0
		|| ft_strcmp(line, "exit") == 0)
		return (true);
	return (false);
}
