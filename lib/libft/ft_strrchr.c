/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:33:58 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:33:40 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = c;
	i = ft_strlen((char *)s);
	while (i > 0)
	{
		if (s[i] == uc)
			return ((char *)&s[i]);
		i--;
	}
	if (s[0] == uc)
		return ((char *)s);
	return (0);
}
