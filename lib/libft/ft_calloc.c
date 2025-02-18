/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:55:22 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:32:15 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;

	mem = (unsigned char *)malloc(nmemb * size);
	if (!mem)
		return (0);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
