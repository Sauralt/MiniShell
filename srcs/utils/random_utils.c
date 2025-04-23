/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/23 16:14:44 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	real_len(char *s, int start, int len, char quote)
{
	int	i;
	int	c;

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
	{
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
	}
	else
	{
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
	}
	free(temp);
	str[j] = '\0';
	return (str);
}

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
