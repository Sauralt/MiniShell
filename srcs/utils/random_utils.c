/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 17:19:04 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && s2)
	{
		res = ft_strdup(s2);
		free(s2);
		return (res);
	}
	if (!s2 && s1)
	{
		res = ft_strdup(s1);
		free(s1);
		return (res);
	}
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

char	**init_str(t_shell *data, char *line)
{
	char	**str;

	str = ft_split(line, ' ');
	if (!str)
		return (NULL);
	str = re_split(data, str);
	if (!str)
		return (NULL);
	str = ft_quote(str, data);
	return (str);
}

void	strdup_param(t_token *t, int i, char **str, int count)
{
	int	j;

	free_str(t->str);
	t->str = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (j < count && str[i] != NULL)
	{
		t->str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	t->str[j] = NULL;
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
