/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:50:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/29 12:39:43 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	real_len(char *s, int start, int len)
{
	int		i;
	int		c;
	char	quote;

	c = 0;
	quote = '\0';
	i = start;
	while (i < start + len)
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (quote == s[i])
			{
				i++;
				c++;
				quote = '\0';
			}
			else if (quote == '\0')
			{
				quote = s[i];
			}
		}
		i++;
	}
	return (len - c);
}

static char	*loop(char *temp, char quote, int j, char *str)
{
	int	i;

	i = 0;
	while (temp[i])
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

static char	*is_dollar(char *s, char *temp)
{
	int		j;
	char	quote;
	char	*str;

	j = 0;
	quote = '\0';
	str = malloc((real_len(temp, 0, ft_strlen(temp)) + 1)
			* sizeof(char));
	if (!str)
		return (s);
	str = loop(temp, quote, j, str);
	free(temp);
	return (str);
}

static char	*no_dollar(char *s, int start, int len, char *temp)
{
	char	*str;

	str = malloc((real_len(s, start, len) + 1) * sizeof(char));
	if (!str)
		return (s);
	str = loop_no_dollar(temp, start, len, str);
	return (str);
}

char	*ft_strndup_no_quote(char *s, int start, int len, t_shell *data)
{
	char	*str;
	char	*temp;

	temp = init_nstr(data, s, start, len);
	if (strcmp(temp, s) == 0)
		str = no_dollar(s, start, len, temp);
	else
		str = is_dollar(s, temp);
	return (str);
}
