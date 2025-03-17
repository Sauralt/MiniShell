/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:27:41 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/17 15:39:04 by marvin           ###   ########.fr       */
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
	char	*path[PATH_MAX];

	(void)argc;
	(void)argv;
	data->cmd = NULL;
	data->rand = NULL;
	data->meta = NULL;
	data->token = NULL;
	data->exit_code = 0;
	data->env = env;
	path = getcwd(path, sizeof(path));
	data->cwd = ft_strdup(path);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	t_stack	*test;
	char	*line;

	data = malloc(sizeof(t_shell));
	signal(SIGINT, handle_sigint);
	while (1)
	{
		init_data(argc, argv, env, data);
		line = readline("Minishell> ");
		if (!line || ft_strcmp(line, "exit") == 0)
			return (1);
		if (ft_strncmp(line, "\0", 2) != 0 && is_builtin(line) == true)
			exec_cmd(line);
		add_history(line);
		if (ft_strncmp(line, "\0", 2) != 0 && init_tokens(data, line) == 1)
			return (1);
		if (ft_strncmp(line, "\0", 2) != 0 && init_stacks(data) == 1)
			return (1);
		proc(data);
		test = data->meta;
		while (test && test->next != data->meta)
		{
			printf("%s\n", test->str);
			test = test->next;
		}
		if (test)
			printf("%s\n", test->str);
		free_all(data, line);
	}
	rl_clear_history();
	return (0);
}
