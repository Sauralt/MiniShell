/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_in_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:30:55 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/23 18:41:10 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_tokens(t_shell *data, char **temp)
{
	int	j;

	j = 0;
	while (temp[j])
	{
		ft_add_token(&data->token, ft_new_token(data, temp[j]));
		j++;
	}
}

static char	**n_token(int i, int start, t_token *t, char **temp)
{
	int	j;

	j = 0;
	while (t->str[0][i])
	{
		start = i;
		if (t->str[0][i] != '\0' && (t->str[0][i] == '<' || t->str[0][i] == '>'
			|| t->str[0][i] == '|'))
		{
			i++;
			if (t->str[0][i] == t->str[0][i - 1])
				i++;
			temp[j] = ft_strndup(t->str[0], start, i - start);
			j++;
		}
		else
		{
			while (t->str[0][i] != '\0' && t->str[0][i] != '<'
				&& t->str[0][i] != '>' && t->str[0][i] != '|')
				i++;
			temp[j] = ft_strndup(t->str[0], start, i - start);
			j++;
		}
	}
	temp[j] = NULL;
	return (temp);
}

int	count_len(t_token *t, int len)
{
	int	i;

	i = 0;
	if (t->str[0][i] == '<' || t->str[0][i] == '>' || t->str[0][i] == '|')
	{
		len += 2;
		i++;
		if (t->str[0][i] == t->str[0][i - 1])
			i++;
	}
	while (t->str[0][i])
	{
		if (t->str[0][i] == '<' || t->str[0][i] == '>' || t->str[0][i] == '|')
		{
			if (t->str[0][i + 1] != t->str[0][i] && t->str[0][i] == '|')
				i++;
			len += 3;
		}
		i++;
	}
	return (len);
}

void	check_meta_in_word(t_shell *data, t_token *t)
{
	int		i;
	int		len;
	int		start;
	char	**temp;

	if (ft_strlen(t->str[0]) == 1 || ft_strlen(t->str[0]) == 2)
		return ;
	i = 0;
	len = 0;
	len = count_len(t, len);
	if (len == 0)
		return ;
	temp = malloc(sizeof(char *) * (len + 1));
	i = 0;
	start = 0;
	temp = n_token(i, start, t, temp);
	while (temp[i])
	{
		printf("%s\n", temp[i]);
		i++;
	}
	new_tokens(data, temp);
	free_str(temp);
}
