/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/22 16:39:45 by cfleuret         ###   ########.fr       */
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
	int		i;
	int		j;
	int		flag;
	char	quote;

	flag = 0;
	j = 0;
	quote = find_quote(s, start, len);
	s = ft_strdup(init_nstr(data, s, start, len));
	str = malloc((real_len(s, start, len, quote) + 1) * sizeof(char));
	//printf("%s\n", str);
	if (!str)
		return (NULL);
	i = start;
	while (i < start + len)
	{
		if (s[i] == quote)
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
			i++;
		}
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	if (flag == 1)
	{
		free(str);
		return (NULL);
	}
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
