/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:25:22 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:54:23 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int				d;
	unsigned int	o;

	d = 0;
	o = (unsigned int)n;
	if (n < 0)
	{
		d++;
		o = (unsigned int)(n * -1);
	}
	if (o == 0)
		d++;
	while (o != 0)
	{
		o /= 10;
		d++;
	}
	return (d);
}

void	fill_nbr_str(unsigned int n, char *str, int n_length)
{
	unsigned int	d;
	unsigned int	r;

	str += n_length;
	*str-- = '\0';
	d = n;
	if (n == 0)
		*str = '0';
	while (d != 0)
	{
		r = d % 10;
		d /= 10;
		*str-- = '0' + r;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	int				n_length;
	unsigned int	o;

	n_length = count_digits(n);
	str = (char *)malloc(sizeof(char) * (n_length + 1));
	if (!str)
		return (0);
	o = (unsigned int)n;
	if (n < 0)
	{
		*str = '-';
		o = (unsigned int)(n * -1);
	}
	fill_nbr_str(o, str, n_length);
	return (str);
}
