/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/26 14:10:59 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell> ");
}

static void	init_data(int argc, char **argv, t_shell *data)
{
	(void)argc;
	(void)argv;
	data->token = NULL;
	data->exit_code = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	t_token	*test;
	char	*line;

	data = malloc(sizeof(t_shell));
	signal(SIGINT, handle_sigint);
	init_env(data, env);
	while (1)
	{
		init_data(argc, argv, data);
		line = readline("Minishell> ");
		if (!line)
			break ;
		add_history(line);
		if (ft_strncmp(line, "\0", 2) != 0 && init_tokens(data, line) == 1)
			break ;
		if (ft_strncmp(line, "\0", 2) != 0)
			proc(data);
		test = data->token;
		// while (test && test->next != data->token)
		// {
		// 	printf("%s\n", test->str[1]);
		// 	test = test->next;
		// }
		// if (test)
		// 	printf("%s\n", test->str[1]);
		free_all(data, line);
	}
	free_env(data->env);
	free_all(data, line);
	free_env(data->env);
	rl_clear_history();
	return (0);
}
