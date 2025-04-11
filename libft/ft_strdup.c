/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfleuret <cfleuret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:38:52 by cfleuret          #+#    #+#             */
/*   Updated: 2025/03/31 16:05:35 by cfleuret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		t;

	copy = NULL;
	t = ft_strlen((char *) src);
	copy = (char *) malloc (t * sizeof(char) + 1);
	if (copy == NULL)
		return (NULL);
	ft_strcpy (copy, (char *) src);
	return (copy);
}
/*int	main(void)
{
	char	str[] = "abc";
	printf("%s\n", ft_strdup(str));
	return (0);
}*/
