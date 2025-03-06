/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/06 16:11:29 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static void	init_data(int argc, char **argv, char **env, t_shell *data)
{
	(void)argc;
	(void)argv;
	data->hist = malloc(sizeof(t_hist));
	data->cmd = malloc(sizeof(t_cmd));
	data->token = malloc(sizeof(t_token));
	data->exit_code = 0;
	data->env = env;
}
int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;

	init_data(argc, argv, env, data);
	while (1)
	{
		line = readline("Minishell> ");
		if (!line)
			return (1);
		if (init_tokens(data, line) == 1)
			return (1);
	}
	return (0);
}
