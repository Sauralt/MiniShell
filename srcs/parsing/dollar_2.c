/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:54:12 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/09 16:47:50 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_dollar(char *str, int i, int *f)
{
	if (str[i] == '$' && str[i + 1] == '?')
	{
		*f = 2;
		return (1);
	}
	if (str[i] == '$' && ft_isdigit(str[i + 1]))
	{
		(*f) = 1;
		return (1);
	}
	else
	{
		(*f) = 0;
		return (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '"'
			&& str[i + 1] != '\'' && str[i + 1] != '='
			&& str[i + 1] != ':' && str[i + 1] != '\0');
	}
}

static char	*extract_dollar_key(char *str, int *i, t_shell *data, int flag)
{
	int		start;
	int		end;

	start = *i;
	(*i)++;
	if (flag == 0)
	{
		while (*i < data->start + data->l && ((str[*i] >= 'A' && str[*i] <= 'Z')
				|| ft_isalnum(str[*i]) || str[*i] == '_') && str[*i] != '$')
			(*i)++;
		end = *i;
	}
	else
	{
		while (*i < data->start + data->l && ft_isdigit(str[*i]))
			(*i)++;
		end = *i;
	}
	return (ft_strndup(str, start, end - start));
}

static void	fill_var_array(t_shell *data, char **var, char *str, int *index)
{
	int		f;
	int		quote;
	char	*temp;

	quote = 0;
	while (index[0] < data->start + data->l)
	{
		quote = quote_flag(quote, str, index[0]);
		if (is_valid_dollar(str, index[0], &f) && quote != 1)
		{
			if (f == 2)
			{
				index[0] += 2;
				var[index[1]++] = ft_itoa(data->exit_code);
				continue ;
			}
			temp = extract_dollar_key(str, &index[0], data, f);
			var[index[1]++] = ft_dollar(data, temp);
		}
		else
			index[0]++;
	}
	var[index[1]] = NULL;
}

char	*change_dollar(t_shell *data, char *str, int len, int i)
{
	char	**var;
	char	*nstr;
	int		index[2];

	var = malloc(sizeof(char *) * (len + 1));
	if (!var)
		return (NULL);
	index[0] = i;
	index[1] = 0;
	fill_var_array(data, var, str, index);
	nstr = change_str(str, var, data, index[1]);
	if (nstr[0] == '\0')
	{
		if (str[data->l +1] == '\0')
			data->exit_code = -1;
		return (str);
	}
	return (nstr);
}
