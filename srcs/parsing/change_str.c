/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:08:25 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/30 11:09:01 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_expandable(char *str, int i, int quote)
{
	return (str[i] == '$' && quote != 1 && str[i + 1] != ' '
		&& str[i + 1] != '"' && str[i + 1] != '=' && str[i + 1] != ':'
		&& str[i + 1] != '\'' && str[i + 1] != '\0');
}

static int	skip_dollar_key(char *str, int i, t_shell *data)
{
	while (i < data->start + data->l
		&& ((str[i] >= 'A' && str[i] <= 'Z')
			|| ft_isascii(str[i]) || str[i] == '_'))
		i++;
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
	int		i;
	int		t;
	int		quote;

	i = data->start;
	quote = 0;
	t = 0;
	nstr = malloc(sizeof(char) * (len_var(data, var) + 1));
	if (!nstr)
		return (NULL);
	while (i < data->start + data->l)
	{
		quote = quote_flag(quote, str, i);
		if (is_expandable(str, i, quote))
		{
			i++;
			i = skip_dollar_key(str, i, data);
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
