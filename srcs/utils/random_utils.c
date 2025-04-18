/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:34:10 by cfleuret          #+#    #+#             */
/*   Updated: 2025/04/18 14:16:07 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_str(t_shell *data, char *line)
{
	char	**str;
	char	**temp;

	str = ft_split(line, ' ');
	if (!str)
		return (NULL);
	str = re_split(data, str);
	if (!str)
		return (NULL);
	temp = str;
	str = ft_quote(str, data);
	if (!str)
		return (ft_dprintf(2, "open quote\n"), temp);
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

char	**change_str(t_shell *data, char **str)
{
	int		i;
	int		j;
	int		new_i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
			{
				new_i = skip(str, str[i][j], i, j);
				if (new_i < 0)
					return (str);
				i = new_i;
				j = change_j(str, str[i][j], i, j);
				if (!str[i] || !str[i][j])
					break ;
			}
			else if (str[i][j] == '$')
			{
				tmp = ft_dollar(data, str[i]);
				if (tmp)
				{
					free(str[i]);
					str[i] = tmp;
					j = -1;
				}
			}
			j++;
		}
		i++;
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
