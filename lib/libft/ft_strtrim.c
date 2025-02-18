/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:39 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:32:50 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	char_in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	trim_len;
	size_t	i;
	char	*str;

	if (!s1)
		return (0);
	start = 0;
	while (char_in_set(s1[start], set))
		start++;
	end = ft_strlen((char *)s1);
	if (start == end - 1)
		return ((char *)s1);
	while (char_in_set(s1[end - 1], set) && start < end)
		end--;
	trim_len = end - start + 1;
	str = (char *)malloc(sizeof (char) * trim_len);
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
