/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:19:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 14:52:45 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_new_tokens(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
		{
			count++;
			if (str[i + 1] == str[i])
				i++;
		}
		i++;
	}
	return (count);
}

static int	fill_parsed_str(const char *str, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_operator(str[i]))
		{
			if (j > 0 && s[j - 1] != ' ')
				s[j++] = ' ';
			s[j++] = str[i];
			if (str[i + 1] == str[i])
				s[j++] = str[i++];
			if (str[i + 1] && str[i + 1] != ' ')
				s[j++] = ' ';
		}
		else
			s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	return (j);
}

static char	*ft_parse(const char *str)
{
	int		len;
	char	*s;

	len = ft_strlen(str) + count_new_tokens(str) + 1;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	fill_parsed_str(str, s);
	return (s);
}

static char	**loop_re_split(char **str, int k, int j, char **new_tokens)
{
	int		i;
	char	**split_result;
	char	*parsed;

	i = 0;
	while (str[i])
	{
		parsed = ft_parse(str[i]);
		split_result = ft_split(parsed, ' ');
		free(parsed);
		k = 0;
		while (split_result[k])
		{
			new_tokens[j] = ft_strdup(split_result[k]);
			j++;
			k++;
		}
		free_str(split_result);
		i++;
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}

char	**re_split(t_shell *data, char **str)
{
	int		i;
	int		j;
	int		k;
	int		total_tokens;
	char	**new_tokens;

	i = 0;
	j = 0;
	k = 0;
	total_tokens = 0;
	while (str[i])
		total_tokens += count_new_tokens(str[i++]);
	new_tokens = malloc(sizeof(char *) * (i + total_tokens + 2));
	if (!new_tokens)
		return (NULL);
	new_tokens = loop_re_split(str, k, j, new_tokens);
	new_tokens = change_str(data, new_tokens);
	free_str(str);
	return (new_tokens);
}
