/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/25 17:07:05 by mgarsaul         ###   ########.fr       */
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

int	ft_unset(t_shell *data, char *cmd)
{
	if (!data || !data->env || !cmd)
		return (1);
	if (ft_strchr(cmd, '='))
	{
		fprintf(stderr, "unset: `%s': not a valid identifier\n", cmd);
		return (data->exit_code = 1);
	}
	remove_env_node(data, cmd);
	return (data->exit_code = 0);
}
