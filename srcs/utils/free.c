/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:38:30 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/30 11:41:38 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *data, char *line)
{
	free(line);
	free_tokens(data->token);
	free_env(data->env);
	free(data);
	rl_clear_history();
}

void	free_str(char **str)
{
	int	i;

	if (!str)
		return ;
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
		if (t->infile != STDIN_FILENO)
			close(t->infile);
		if (t->outfile != STDOUT_FILENO)
			close(t->outfile);
		delfirst(&t);
	}
}

void	free_env(t_env *env)
{
	while (env)
	{
		delfirst_stack(&env);
	}
}

void	ft_close(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
