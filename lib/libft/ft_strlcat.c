/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:43:40 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:31:38 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen((char *)dst);
	src_len = ft_strlen((char *)src);
	if (size < dst_len)
		dst_len = size;
	if (dst_len == size)
		return (dst_len + src_len);
	return (dst_len + ft_strlcpy(dst + dst_len, src, size - dst_len));
}
/*
int	main(void)
{
	char	dst[100] = "this is the dest string";
	char	src[] = "this is the source string";
	size_t	ret;

	ret = ft_strlcat(dst, src, 30);
	printf("ret: %d cat: %s\n", ret, dst);
	return (0);
}
*/
