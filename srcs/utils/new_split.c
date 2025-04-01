/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:19:28 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/01 16:17:50 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	is_it_double(char **str, int i, int j)
// {
// 	if (str[i][j] == str[i][j + 1])
// 		j++;
// 	else if (str[i][j] != str[i][j + 1]
// 		&& (str[i][j + 1] == '>' || str[i][j + 1] == '<'))
// 		return (-1);
// 	return (j);
// }

// static char	*ft_parse(char **str, int i, int j)
// {
// 	char	*s;
// 	int		len;

// 	j = 0;
// 	len = ft_strlen(str[i]);
// 	while (str[i][j])
// 	{
// 		if ((str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|'))
// 		{
// 			len++;
// 			if (str[i][j + 1] == str[i][j] && str[i][j] != '|')
// 				j++;
// 		}
// 		j++;
// 	}
// 	j = 0;
// 	s = malloc(sizeof(char) * (len + 2));
// 	len = 0;
// 	while (str[i][j])
// 	{
// 		if ((str[i][j + 1] == '<' || str[i][j + 1] == '>'
// 			|| str[i][j + 1] == '|') && str[i][j + 1] != str[i][j])
// 		{
// 			s[len] = str[i][j];
// 			len++;
// 			s[len] = ' ';
// 		}
// 		else if (str[i][j] == '<' || str[i][j] == '>'
// 			|| str[i][j] == '|')
// 		{
// 			if (str[i][j + 1] != str[i][j])
// 			{
// 				s[len] = str[i][j];
// 				len++;
// 				s[len] = ' ';
// 			}
// 			else
// 			{
// 				s[len] = str[i][j];
// 				len++;
// 				j++;
// 				s[len] = str[i][j];
// 				len++;
// 				s[len] = ' ';
// 			}
// 		}
// 		else
// 			s[len] = str[i][j];
// 		len++;
// 		j++;
// 	}
// 	s[len] = '\0';
// 	return (s);
// }

// static char	**check_meta(char **str, int i)
// {
// 	int		j;
// 	char	*s;

// 	j = 0;
// 	while (str[i][j])
// 	{
// 		if ((str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|'))
// 		{
// 			if (j == 0 && str[i][j + 1] == '\0')
// 				return (str);
// 			else
// 			{
// 				s = ft_parse(str, i, j);
// 				return (ft_split(s, ' '));
// 			}
// 		}
// 		j++;
// 	}
// 	return (str);
// }

// static char	**spliting(char **str, char **nstr, int n, int i)
// {
// 	char	**check;
// 	int		len;
// 	int		j;
// 	int		k;

// 	check = 0;
// 	len = i + n + 1;
// 	nstr = malloc(sizeof(char *) * len);
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (i < len - 1)
// 	{
// 		check = check_meta(str, j);
// 		if (check == str)
// 			nstr[i] = ft_strdup(str[j]);
// 		else
// 		{
// 			k = 0;
// 			while (check[k])
// 			{
// 				nstr[i] = ft_strdup(check[k]);
// 				k++;
// 				i++;
// 			}
// 		}
// 		free_str(check);
// 		i++;
// 		j++;
// 	}
// 	nstr[i] = NULL;
// 	return (nstr);
// }

// char	**re_split(char **str)
// {
// 	int		n;
// 	int		i;
// 	int		j;
// 	char	**nstr;

// 	n = 0;
// 	i = 0;
// 	nstr = NULL;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i][j])
// 		{
// 			if (str[i][j] == '<' || str[i][j] == '>' || str[i][j] == '|')
// 			{
// 				j = is_it_double(str, i, j);
// 				if (j == -1)
// 					return (NULL);
// 				n++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	nstr = spliting(str, nstr, n, i);
// 	i = 0;
// 	while (nstr[i])
// 	{
// 		printf("%s\n", nstr[i]);
// 		i++;
// 	}
// 	return (nstr);
// }

static int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

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

static char	*ft_parse(const char *str)
{
	int		len;
	char	*s;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	s = malloc(len);
	len = strlen(str) + count_new_tokens(str) + 1;
	if (!s)
		return (NULL);
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
	return (s);
}

char	**re_split(char **str)
{
	int		i = 0, j = 0, k = 0, total_tokens = 0;
	char	**new_tokens;
	char	**split_result;
	char	*parsed;

	while (str[i])
		total_tokens += count_new_tokens(str[i++]);
	new_tokens = malloc(sizeof(char *) * (i + total_tokens + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	while (str[i])
	{
		parsed = ft_parse(str[i]);
		split_result = ft_split(parsed, ' ');
		free(parsed);
		k = 0;
		while (split_result[k])
			new_tokens[j++] = split_result[k++];
		free(split_result);
		i++;
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}

