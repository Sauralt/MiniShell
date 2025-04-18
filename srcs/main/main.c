/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 14:16:19 by mgarsaul         ###   ########.fr       */
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
	data->del_num = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;

	data = malloc(sizeof(t_shell));
	data->exit_code = 0;
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
		free_all(data, line);
	}
	free_env(data->env);
	free_all(data, line);
	free(data);
	rl_clear_history();
	return (0);
}
