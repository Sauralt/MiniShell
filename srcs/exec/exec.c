/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:58:48 by cfleuret          #+#    #+#             */
/*   Updated: 2025/06/12 15:16:14 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_built(t_shell *data, t_token *cmd, int flag)
{
	redirected(cmd);
	if (ft_strncmp(cmd->str[0], "pwd", 4) == 0)
		ft_pwd(data, cmd);
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
		ft_exit(data, cmd, flag);
}

int	builtin(t_shell *data, t_token *cmd, int *original, int flag)
{
	pid_t	pid;

	if (is_builtin(cmd->str[0]) && flag != 2)
	{
		if ((cmd->infile < 0 || cmd->outfile < 0) && flag == 0)
		{
			if (cmd->infile == -1)
				ft_dprintf(2, "%s: No such file or directory\n", cmd->invalid);
			if (cmd->infile == -2 || cmd->outfile == -2)
				ft_dprintf(2, "%s: Permission denied\n", cmd->invalid);
			if (cmd->infile == -3 || cmd->outfile == -3)
				ft_dprintf(2, "%s: Is a directory\n", cmd->invalid);
			cmd->exit_code = 1;
			return (0);
		}
		if (flag == 1)
			close_origin(original);
		exec_built(data, cmd, flag);
		if (flag == 1)
			free_exit(data, flag);
		return (0);
	}
	if (!is_builtin(cmd->str[0]) || flag != 2)
		return (1);
	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		if ((cmd->infile < 0 || cmd->outfile < 0))
		{
			if (cmd->infile == -1)
				ft_dprintf(2, "%s: No such file or directory\n", cmd->invalid);
			if (cmd->infile == -2 || cmd->outfile == -2)
				ft_dprintf(2, "%s: Permission denied\n", cmd->invalid);
			if (cmd->infile == -3 || cmd->outfile == -3)
				ft_dprintf(2, "%s: Is a directory\n", cmd->invalid);
			free_exec_simple(data, cmd, original, 1);
		}
		signal(SIGQUIT, SIG_DFL);
		close_origin(original);
		exec_built(data, cmd, flag);
		exit_proc(data, 0, 0, cmd);
	}
	data->pids[data->l++] = pid;
	return (0);
}

static void	handle_pipeline(t_shell *data, t_token *t, int *original)
{
	int		fd[2];

	data->pids = malloc(sizeof(pid_t) * (data->func_num + 1));
	if (!data->pids)
		return ;
	while (t && t->next && t->next != data->token && g_signal_pid != 2)
	{
		if (exec_flag(data, t) == 0)
			break ;
		if (t->exit_code == 0 && t->type != 2 && t->type != 3)
			ft_pipe(fd, original, data, t);
		else
			data->exit_code = t->exit_code;
		t = t->next;
	}
	while ((t->type == 2 || t->type == 3) && t != data->token)
		t = t->next;
	if (t && t->type != 2 && t->type != 3
		&& t->exit_code == 0 && g_signal_pid != 2)
	{
		if (builtin(data, t, original, 2) == 1)
			exec_simple(data, t, original, 1);
	}
	waitall(data);
	free(data->pids);
}

static void	exec(t_shell *data, t_token *t, int *original)
{
	int	flag;

	data->l = 0;
	data->prev_fd = -1;
	g_signal_pid = 1;
	flag = exec_flag(data, t);
	while ((t->type == 2 || t->type == 3) && t != data->token)
		t = t->next;
	if (t->type == 0 && flag == 0)
	{
		ft_dprintf(2, "%s: command not found\n", t->str[0]);
		data->exit_code = 127;
		return ;
	}
	if (flag == 0)
	{
		not_pipe(data, t, original);
		return ;
	}
	else
		handle_pipeline(data, t, original);
}

int	proc(t_shell *data)
{
	t_token	*t;
	int		original[2];

	original[0] = dup(STDIN_FILENO);
	original[1] = dup(STDOUT_FILENO);
	t = data->token;
	if (data->token->type == 2 && (data->token->next->type == 2
			|| data->token->next->type == 1))
	{
		close_dup(original[0], original[1]);
		return (0);
	}
	while (t->type != 1 && t->next != data->token)
		t = t->next;
	if (t->next == data->token)
		t = t->next;
	exec(data, t, original);
	close_dup(original[0], original[1]);
	return (0);
}
