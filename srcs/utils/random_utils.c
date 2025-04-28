/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/28 15:49:39 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*loop_no_dollar(char *temp, int start, int len, char *str)
{
	int		i;
	int		j;
	char	quote;

	i = start;
	j = 0;
	quote = '\0';
	while (i < start + len)
	{
		if ((temp[i] == '\'' || temp[i] == '"') && quote == '\0')
		{
			quote = temp[i];
			i++;
		}
		else if (temp[i] == quote)
		{
			quote = '\0';
			i++;
		}
		else
			str[j++] = temp[i++];
	}
	str[j] = '\0';
	return (str);
}

void	change_tok_str(t_token *t, char *str, int len, t_shell *data)
{
	int		i;
	t_token	*temp;
	t_token	*temp2;

	t->str[0] = str;
	temp = t->next;
	len--;
	i = 1;
	while (len > 0)
	{
		temp2 = temp->next;
		t->str[i] = ft_strdup(temp->str[0]);
		delone(data, temp);
		temp = temp2;
		i++;
		len--;
	}
	t->str[i] = NULL;
}
