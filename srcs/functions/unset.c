/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/27 17:22:12 by cfleuret         ###   ########.fr       */
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

int	ft_unset(t_shell *data, t_token *str)
{
	int	i;

	i = 0;
	while (str->str[i])
	{
		if (!data || !data->env || !str->str[i])
			return (1);
		if (ft_strchr(str->str[i], '='))
		{
			printf("unset: `%s': not a valid identifier\n", str->str[i]);
			return (data->exit_code = 1);
		}
		remove_env_node(data, str->str[i]);
		i++;
	}
	return (data->exit_code = 0);
}
