/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 17:28:49 by cfleuret         ###   ########.fr       */
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
	t_stack	*test;
	char	*line;

	data = malloc(sizeof(t_shell));
	while (1)
	{
		init_data(argc, argv, env, data);
		line = readline("Minishell> ");
		if (!line)
			return (1);
		if (init_tokens(data, line) == 1)
			return (1);
		if (init_stacks(data) == 1)
			return (1);
		test = data->meta;
		while (test && test->next != data->meta)
		{
			printf("%s\n", test->str);
			test = test->next;
		}
		if (test)
			printf("%s\n", test->str);
		free(line);
		free_stack(data->cmd);
		free_stack(data->rand);
		free_stack(data->meta);
		free_tokens(data->token);
	}
	return (0);
}
