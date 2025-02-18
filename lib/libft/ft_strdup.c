/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:05:42 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:31:00 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dups;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	dups = (char *)malloc(s_len * sizeof(unsigned char) + 1);
	if (!dups)
		return (0);
	ft_memcpy(dups, s, s_len + 1);
	return (dups);
}
