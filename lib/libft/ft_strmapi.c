/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:51:33 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:31:35 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		s_len;
	int		i;
	char	*str;

	s_len = ft_strlen((char *)s);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < s_len)
	{
		str[i] = f((int)i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
