/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/05/09 10:53:26 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	remove_env_node(t_shell *data, const char *key)
{
	t_env	*curr;
	t_env	*to_delete;
	size_t	len;

	if (!data->env || !key)
		return ;
	len = ft_strlen(key);
	curr = data->env->next;
	while (curr != data->env)
	{
		if (ft_strncmp(curr->str, key, len) == 0 && curr->str[len] == '=')
		{
			to_delete = curr;
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				data->env = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free(to_delete->str);
			free(to_delete);
			return ;
		}
		curr = curr->next;
	}
}

bool	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (false);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	ft_unset(t_shell *data, t_token *str)
{
	int	i;

	i = 1;
	while (str->str[i])
	{
		if (!is_valid_identifier(str->str[i]))
		{
			ft_dprintf(2, "unset: `%s': not a valid identifier\n", str->str[i]);
			data->exit_code = 1;
		}
		else
			remove_env_node(data, str->str[i]);
		i++;
	}
	data->exit_code = 0;
	return (data->exit_code);
}
