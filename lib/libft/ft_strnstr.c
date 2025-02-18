/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:14:30 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:32:47 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;
	size_t	i;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen((char *)little);
	big_len = ft_strlen((char *)big);
	if (big_len > len)
		big_len = len;
	i = 0;
	while (i + little_len <= big_len)
	{
		if (!ft_strncmp(&big[i], little, little_len))
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char str[] = "needle";
	printf("%s", ft_strnstr(str, str, 5));
	return (0);
}
*/
