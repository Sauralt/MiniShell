/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:06:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/05/09 15:33:58 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_exec(t_shell *data, t_token *t, int *fd)
{
	pid_t	pid;
	int		status;

	if (t->type == 0)
	{
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
		data->exit_code = 127;
		return ;
	}
	if (t->type == 1)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid < 0)
		{
			ft_close(fd);
			return (perror("fork"));
		}
		if (pid == 0 && t->type != 2)
		{
			child_process(t, data, fd);
			ft_close(fd);
		}
		if (t->next && ft_strcmp(t->next->str[0], "|") == 0)
			dup2(fd[0], STDIN_FILENO);
		ft_close(fd);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			t->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			t->exit_code = 128 + WTERMSIG(status);
		else
			t->exit_code = 1;
	}
}

int	check_tok_order(t_shell *data)
{
	t_token	*t;

	t = data->token;
	if (t->str[0][0] == '|')
	{
		data->exit_code = 2;
		return (ft_dprintf(2, " syntax error near unexpected token `%s'\n",
				t->str[0]), 2);
	}
	while (t->next != data->token)
	{
		if ((t->type == 2 && ft_strcmp(t->str[0], t->next->str[0]) == 0)
			|| (t->type == 2 && t->next->str[0][0] == '|'))
		{
			data->exit_code = 2;
			return (ft_dprintf(2, " syntax error near unexpected token `%s'\n",
					t->next->str[0]), 2);
		}
		t = t->next;
	}
	if (t->type == 2)
	{
		data->exit_code = 2;
		return (ft_dprintf(2, " syntax error near unexpected token `newline'\n")
			, 2);
	}
	return (0);
}

char	*find_absolute(char *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*ncmd;

	len = ft_strlen(cmd);
	i = len;
	while (cmd[i] != '/' && i != 0)
		i--;
	if (i == 0)
		return (cmd);
	i++;
	ncmd = malloc(sizeof(char) * (len - i + 1));
	if (!ncmd)
		return (cmd);
	j = 0;
	while (cmd[i])
	{
		ncmd[j] = cmd[i];
		i++;
		j++;
	}
	ncmd[j] = '\0';
	free(cmd);
	return (ncmd);
}

int	last_init(t_token *c, t_shell *data, char *content)
{
	if (!c->str[0])
	{
		free_str(c->str);
		free(c);
		return (1);
	}
	c->type = set_token_type(data, content);
	c->str[1] = NULL;
	c->infile = 0;
	c->outfile = 1;
	c->exit_code = 0;
	c->next = c;
	c->prev = c;
	return (0);
}
