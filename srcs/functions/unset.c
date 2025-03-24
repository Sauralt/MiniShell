/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:22:58 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/03/24 17:02:14 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	remove_env_node(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*to_delete;
	size_t	len;

	if (!env || !*env || !key)
		return ;
	len = ft_strlen(key);
	curr = *env;
	while (curr)
	{
		if (ft_strncmp(curr->str, key, len) == 0 && curr->str[len] == '=')
		{
			to_delete = curr;
			if (curr->prev)
				curr->prev->next = curr->next;
			else
				*env = curr->next;
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
	int	i;

	if (!data || !data->env || !cmd || !cmd[1])
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (ft_strchr(&cmd[i], '='))
		{
			fprintf(stderr, "unset: `%c': not a valid identifier\n", cmd[i]);
			data->exit_code = 1;
		}
		else
		{
			remove_env_node(&data->env, &cmd[i]);
			data->exit_code = 0;
		}
		i++;
	}
	return (data->exit_code);
}
