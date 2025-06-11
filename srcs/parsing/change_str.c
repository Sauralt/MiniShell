/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:08:25 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/20 15:26:29 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_expandable(char *str, int i, int quote, int *f)
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
		return (str[i] == '$' && quote != 1 && str[i + 1] != ' '
			&& str[i + 1] != '"' && str[i + 1] != '\t'
			&& str[i + 1] != '\'' && str[i + 1] != '='
			&& str[i + 1] != ':' && str[i + 1] != '\0');
	}
}

static int	skip_dollar_key(char *str, int i, t_shell *data, int flag)
{
	if (flag == 2)
	{
		i++;
	}
	if (flag == 0)
	{
		while (i < data->start + data->l
			&& ((str[i] >= 'A' && str[i] <= 'Z')
				|| (ft_isalnum(str[i])) || str[i] == '_'
				|| str[i] == '_') && str[i] != '$')
			i++;
	}
	else
	{
		while (i < data->start + data->l && ft_isdigit(str[i]))
			i++;
	}
	return (i);
}

static int	insert_var(char *nstr, char *var, int t)
{
	int	k;

	k = 0;
	while (var && var[k])
		nstr[t++] = var[k++];
	return (t);
}

static char	*build_final_string(char *str, char **var, t_shell *data, int j)
{
	char	*nstr;
	int		f;
	int		i;
	int		t;
	int		quote;

	i = data->start;
	quote = 0;
	t = 0;
	nstr = malloc(sizeof(char) * (len_var(data, var) + 1));
	while (i < data->start + data->l)
	{
		quote = quote_flag(quote, str, i);
		if (is_expandable(str, i, quote, &f))
		{
			i++;
			i = skip_dollar_key(str, i, data, f);
			t = insert_var(nstr, var[j++], t);
		}
		else
			nstr[t++] = str[i++];
	}
	nstr[t] = '\0';
	return (nstr);
}

char	*change_str(char *str, char **var, t_shell *data, int j)
{
	char	*nstr;

	j = 0;
	nstr = build_final_string(str, var, data, j);
	free_str(var);
	return (nstr);
}
