/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/18 17:49:27 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell> ");
}

static void	init_data(int argc, char **argv, char **env, t_shell *data)
{
	(void)argc;
	(void)argv;
	data->token = NULL;
	data->exit_code = 0;
	data->env = env;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	t_token	*test;
	char	*line;

	data = malloc(sizeof(t_shell));
	signal(SIGINT, handle_sigint);
	while (1)
	{
		init_data(argc, argv, env, data);
		line = readline("Minishell> ");
		if (!line)
			break ;
		add_history(line);
		if (ft_strncmp(line, "\0", 2) != 0 && init_tokens(data, line) == 1)
			break ;
		if (proc(data) == 1)
			break ;
		test = data->token;
		while (test && test->next != data->token)
		{
			printf("%d\n", test->type);
			test = test->next;
		}
		if (test)
			printf("%d\n", test->type);
		free_all(data, line);
	}
	free_all(data, line);
	rl_clear_history();
	return (0);
}
