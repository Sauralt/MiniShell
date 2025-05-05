/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/05 15:14:41 by cfleuret         ###   ########.fr       */
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
	data->del_num = 0;
}

static int	conditions(t_shell *data, char *line)
{
	int		tok;

	tok = init_tokens(data, line);
	if (ft_strncmp(line, "\0", 2) != 0 && tok == 1)
		return (1);
	if (ft_strncmp(line, "\0", 2) != 0 && tok != 2 && data->exit_code == 0)
		proc(data);
	if (ft_strncmp(line, "\0", 2))
		add_history(line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;

	data = malloc(sizeof(t_shell));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	init_env(data, env);
	while (1)
	{
		init_data(argc, argv, data);
		line = readline("Minishell> ");
		if (!line)
			break ;
		if (conditions(data, line) == 1)
			break ;
		free(line);
		free_tokens(data->token);
	}
	free_all(data, line);
	return (0);
}
