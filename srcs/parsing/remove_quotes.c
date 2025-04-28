/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:50:08 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/28 14:22:51 by cfleuret         ###   ########.fr       */
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
				quote = s[i];
		}
		i++;
	}
	return (len - c);
}

static char	*is_dollar(char *s, char *temp)
{
	int		i;
	int		j;
	char	*str;
	char	quote;

	j = 0;
	quote = '\0';
	str = malloc((real_len(temp, 0, ft_strlen(temp)) + 1)
			* sizeof(char));
	if (!str)
		return (s);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\'' || temp[i] == '"')
		{
			printf("temp[i] avant = %c\n", temp[i]);
			printf("quote avant = %c\n", quote);
			if (quote == temp[i])
			{
				i++;
				quote = '\0';
			}
			else if (quote == '\0')
				quote = temp[i];
			printf("temp[i] apres = %c\n", temp[i]);
			printf("quote apres = %c\n", quote);
		}
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
	char	*str;
	char	quote;
	int		i;
	int		j;

	j = 0;
	quote = '\0';
	str = malloc((real_len(s, start, len) + 1) * sizeof(char));
	if (!str)
		return (s);
	i = start;
	while (i < start + len)
	{
		if (temp[i] == '\'' || temp[i] == '"')
		{
			if (quote == temp[i])
			{
				i++;
				quote = '\0';
			}
			else if (quote == '\0')
				quote = temp[i];
		}
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

	temp = ft_strdup(init_nstr(data, s, start, len));
	if (strcmp(temp, s) == 0)
		str = no_dollar(s, start, len, temp);
	else
		str = is_dollar(s, temp);
	free(temp);
	return (str);
}
