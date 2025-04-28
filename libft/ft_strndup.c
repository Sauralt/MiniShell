/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:24:39 by marvin            #+#    #+#             */
/*   Updated: 2025/04/22 14:30:24 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int start, int len)
{
	char	*str;
	int		i;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
