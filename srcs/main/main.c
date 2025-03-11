/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 16:22:46 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static void	init_data(int argc, char **argv, char **env, t_shell *data)
{
	(void)argc;
	(void)argv;
	data->cmd = NULL;
	data->rand = NULL;
	data->meta = NULL;
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
	init_data(argc, argv, env, data);
	while (1)
	{
		line = readline("Minishell> ");
		if (!line)
			return (1);
		if (init_tokens(data, line) == 1)
			return (1);
		if (init_stacks(data) == 1)
			return (1);
		test = data->token;
		while (test && test->next != data->token)
		{
			printf("%d\n", test->type);
			test = test->next;
		}
		printf("%d\n", test->type);
	}
	return (0);
}
