/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarsaul <mgarsaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:09 by mgarsaul          #+#    #+#             */
/*   Updated: 2025/04/17 17:15:25 by mgarsaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_dollar_poll(t_shell *data, char **str)
{
	char	*tmp;
	char	*new_str;
	char	*after_dollar;

	if (!str || !*str)
		return (NULL);
	if (ft_strncmp(*str, "$?", 2) != 0)
		return (*str);
	tmp = ft_itoa(data->exit_code);
	if (!tmp)
		return (NULL);
	after_dollar = *str + 2;
	new_str = ft_strjoin(tmp, after_dollar);
	free(tmp);
	if (!new_str)
		return (NULL);
	// free(*str);
	*str = new_str;
	return (*str);
}

// char	*ft_dollar(t_shell *data, char *str)
// {
// 	t_env	*env;
// 	char	*tmp;
// 	t_env	*start;
// 	size_t	var_len;

// 	if (ft_strncmp(str, "$?", 2) == 0)
// 		return (ft_dollar_poll(data, &str));
// 	env = data->env;
// 	if (!env || !str || str[0] != '$' || !str[1])
// 		return (ft_strdup(str));
// 	start = env;
// 	var_len = ft_strlen(str + 1);
// 	while (env)
// 	{
// 		if (ft_strncmp(env->str, str + 1, var_len) == 0
// 			&& env->str[var_len] == '=')
// 		{
// 			tmp = ft_strchr(env->str, '=');
// 			if (tmp && *(tmp + 1))
// 				return (ft_strdup(tmp + 1));
// 		}
// 		env = env->next;
// 		if (env == start)
// 			break ;
// 	}
// 	return (ft_strdup(""));
// }

char	*ft_dollar(t_shell *data, char *str)
{
	t_env	*env;
	char	*var_name;
	char	*tmp;
	size_t	len;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	if (ft_strncmp(str, "$?", 2) == 0)
		return (ft_dollar_poll(data, &str));
	len = 0;
	while (str[len + 1] && (ft_isalnum(str[len + 1]) || str[len + 1] == '_'))
		len++;
	var_name = ft_substr(str, 1, len);
	if (!var_name)
		return (ft_strdup(""));
	env = find_env(data->env, var_name);
	free(var_name);
	if (env)
	{
		if (ft_strncmp(env->str, str + 1, var_len) == 0
			&& env->str[var_len] == '=')
		{
			tmp = ft_strchr(env->str, '=');
			if (tmp && *(tmp + 1))
				return (ft_strdup(tmp + 1));
		}
		env = env->next;
		if (env == start)
			break ;
	}
	return (ft_strdup(""));
}
