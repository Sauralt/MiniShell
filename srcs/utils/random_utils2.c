/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:48:11 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/18 14:50:24 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static bool	handle_quotes(char **str, int *i, int *j)
{
	int	new_i;

	new_i = skip(str, str[*i][*j], *i, *j);
	if (new_i < 0)
		return (false);
	*i = new_i;
	*j = change_j(str, str[*i][*j], *i, *j);
	return (str[*i] && str[*i][*j]);
}

static bool	handle_dollar(t_shell *data, char **str, int i, int *j)
{
	char	*tmp;

	tmp = ft_dollar(data, str[i]);
	if (!tmp)
		return (true);
	free(str[i]);
	str[i] = tmp;
	*j = -1;
	return (true);
}

char	**change_str(t_shell *data, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\'' || str[i][j] == '"')
			{
				if (!handle_quotes(str, &i, &j))
					break ;
			}
			else if (str[i][j] == '$')
			{
				if (!handle_dollar(data, str, i, &j))
					break ;
			}
			j++;
		}
		i++;
	}
	return (str);
}
