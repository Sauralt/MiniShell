/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:50:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/24 13:10:58 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	real_len(char *s, int start, int len, char quote)
{
	int		i;
	int		c;

	c = 0;
	i = start;
	while (i < start + len)
	{
		if (s[i] == quote)
			c++;
		i++;
	}
	return (len - c);
}

char	find_quote(char *s, int start, int len)
{
	int		i;
	char	quote;

	i = start;
	quote = 0;
	while (i < start + len)
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			quote = s[i];
			break ;
		}
		i++;
	}
	return (quote);
}

static char	*is_dollar(char *s, int start, int len, char *temp)
{
	int		i;
	int		j;
	char	*str;
	char	quote;

	i = 0;
	j = 0;
	str = malloc((real_len(temp, 0, ft_strlen(temp), quote) + 1)
			* sizeof(char));
	if (!str)
		return (s);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == quote)
			i++;
		else
		{
			str[j] = temp[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

static char	*no_dollar(char *s, int start, int len, char *temp)
{
	char	quote;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc((real_len(s, start, len, quote) + 1) * sizeof(char));
	if (!str)
		return (s);
	i = start;
	while (i < start + len)
	{
		if (temp[i] == quote)
			i++;
		else
		{
			str[j] = temp[i];
			i++;
			j++;
		}
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strndup_no_quote(char *s, int start, int len, t_shell *data)
{
	char	*str;
	char	*temp;
	char	quote;
	int		i;
	int		j;

	j = 0;
	quote = find_quote(s, start, len);
	temp = ft_strdup(init_nstr(data, s, start, len));
	if (strcmp(temp, s) == 0)
		str = no_dollar(s, start, len, temp);
	else
		str = is_dollar(s, start, len, temp);
	free(temp);
	return (str);
}
