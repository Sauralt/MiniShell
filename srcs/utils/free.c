/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/11 17:11:39 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<<< HEAD:srcs/utils/free.c
void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tokens(t_token *t)
{
	while (t)
	{
		delfirst(&t);
	}
}

void	free_stack(t_stack *t)
{
	while (t)
	{
		delfirst_stack(&t);
	}
========
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
>>>>>>>> 076f4e3379ee05472da216ef48e5578a2ed3124e:srcs/main/main.c
}
