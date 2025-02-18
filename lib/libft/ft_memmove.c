/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:56:16 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:54:46 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr_src;
	char	*ptr_dest;

	if (!dest && !src)
		return (0);
	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (dest <= src)
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	else
	{
		ptr_dest += n - 1;
		ptr_src += n - 1;
		while (n--)
			*ptr_dest-- = *ptr_src--;
	}
	return (dest);
}
