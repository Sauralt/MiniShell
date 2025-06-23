/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/23 14:16:36 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

int	g_signal_pid;

void	handle_sigint(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	if (g_signal_pid == 1)
		g_signal_pid = sig;
	if (g_signal_pid <= 0 || g_signal_pid == 130)
		rl_redisplay();
	g_signal_pid = 130;
}

static void	init_data(int argc, char **argv, t_shell *data)
{
	(void)argc;
	(void)argv;
	data->token = NULL;
	data->del_num = 0;
	data->func_num = 0;
	data->invalid = 0;
}

static int	conditions(t_shell *data, char *line)
{
	int		tok;

	tok = init_tokens(data, line);
	if (ft_strncmp(line, "\0", 2) != 0 && tok == 1)
		return (1);
	if (ft_strncmp(line, "\0", 2) != 0 && tok != 2 && data->invalid == 0)
		proc(data);
	if (ft_strncmp(line, "\0", 2))
		add_history(line);
	return (0);
}

static int	conditions(t_shell *data, char *line)
{
	int		tok;

	tok = init_tokens(data, line);
	if (ft_strncmp(line, "\0", 2) != 0 && tok == 1)
		return (1);
	if (ft_strncmp(line, "\0", 2) != 0 && tok != 2)
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
	data->exit_code = 0;
	while (1)
	{
		init_data(argc, argv, data);
		line = readline("Minishell> ");
		if (g_signal_pid != 0)
			data->exit_code = g_signal_pid;
		if (!line)
			break ;
		if (conditions(data, line) == 1)
			break ;
		free(line);
		free_tokens(data->token);
		ft_check_signals(data);
	}
	free_all(data, line);
	printf("exit\n");
	return (0);
}
