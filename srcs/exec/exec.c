/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/30 15:55:59 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_built(t_shell *data, t_token *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		ft_pwd(data);
	else if (ft_strncmp(cmd->str[0], "env", 4) == 0)
		ft_env(data);
	else if (ft_strncmp(cmd->str[0], "cd", 3) == 0 && cmd->next == cmd->prev)
		ft_cd(data, cmd);
	else if (ft_strncmp(cmd->str[0], "echo", 5) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->str[0], "export", 7) == 0)
		ft_export(data, cmd);
	else if (ft_strncmp(cmd->str[0], "unset", 6) == 0)
		ft_unset(data, cmd);
	else if (ft_strncmp(cmd->str[0], "exit", 5) == 0)
		ft_exit(data, cmd);
}

int	builtin(t_shell *data, t_token *cmd)
{
	if (ft_strcmp(cmd->str[0], "echo") == 0
		|| ft_strcmp(cmd->str[0], "cd") == 0
		|| ft_strcmp(cmd->str[0], "pwd") == 0
		|| ft_strcmp(cmd->str[0], "export") == 0
		|| ft_strcmp(cmd->str[0], "unset") == 0
		|| ft_strcmp(cmd->str[0], "env") == 0
		|| ft_strcmp(cmd->str[0], "exit") == 0)
	{
		exec_built(data, cmd);
		return (0);
	}
	return (1);
}

static void	handle_pipeline(t_shell *data, t_token *t)
{
	int		fd[2];
	pid_t	pid;

	while (t->next != data->token)
	{
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
				child_process(t, data, fd);
			dup2(fd[0], STDIN_FILENO);
			ft_close(fd);
			waitpid(pid, NULL, 0);
		}
		t = t->next;
	}
	if (builtin(data, t) == 1 && t->type != 2 && exec_simple(data, t) == 1)
		perror("exec");
}

void	exec(t_shell *data, t_token *t)
{
	if (ft_strcmp(t->next->str[0], "|") != 0)
	{
		if (builtin(data, t) == 1 && t->type != 2)
		{
			if (exec_simple(data, t) == 1)
				perror("fork");
		}
		return ;
	}
	handle_pipeline(data, t);
}

int	proc(t_shell *data)
{
	t_token	*t;
	int		original_stdin;
	int		original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	t = data->token;
	if (data->token->type == 2 && data->token->next->type == 2
		&& data->token->next->type == 1)
		return (ft_dprintf(2, "syntax error\n"), 0);
	if (data->token->str[0][0] == '/')
		return (ft_dprintf(2, "%s: is a directory\n", data->token->str[0]), 0);
	while (t->type != 1 && t->next != data->token)
		t = t->next;
	if (t->next == data->token)
		t = t->next;
	exec(data, t);
	close_dup(original_stdin, original_stdout);
	return (0);
}
