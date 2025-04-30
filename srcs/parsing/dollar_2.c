/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:54:12 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/30 11:08:51 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_dollar(char *str, int i)
{
	return (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '"'
		&& str[i + 1] != '\'' && str[i + 1] != '='
		&& str[i + 1] != ':' && str[i + 1] != '\0');
}

static char	*extract_dollar_key(char *str, int *i, t_shell *data)
{
	int		start;
	int		end;

	start = *i;
	(*i)++;
	while (*i < data->start + data->l && ((str[*i] >= 'A' && str[*i] <= 'Z')
			|| ft_isascii(str[*i]) || str[*i] == '_'))
		(*i)++;
	end = *i;
	return (ft_strndup(str, start, end - start));
}

static void	fill_var_array(t_shell *data, char **var, char *str, int *index)
{
	int		i;
	int		j;
	int		quote;
	char	*temp;

	i = index[0];
	j = index[1];
	quote = 0;
	while (i < data->start + data->l)
	{
		quote = quote_flag(quote, str, i);
		if (is_valid_dollar(str, i) && quote != 1)
		{
			temp = extract_dollar_key(str, &i, data);
			var[j++] = ft_dollar(data, temp);
		}
		else
			i++;
	}
	index[0] = i;
	index[1] = j;
	var[j] = NULL;
}

char	*change_dollar(t_shell *data, char *str, int len, int i)
{
	char	**var;
	int		index[2];

	var = malloc(sizeof(char *) * (len + 1));
	if (!var)
		return (NULL);
	index[0] = i;
	index[1] = 0;
	fill_var_array(data, var, str, index);
	return (change_str(str, var, data, index[1]));
}
