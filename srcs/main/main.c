/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/06 13:12:14 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nminishell> ");
}

int	main(int argc, char **argv)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (!line || ft_strcmp(line, "exit") == 0)
			break ;
		if (is_builtin(line) == true)
			exec_cmd(line);
		add_history(line);
		free(line);
	}
	rl_clear_history();
	argc = 1;
	argv[0] = argv[1];
	return (0);
}
