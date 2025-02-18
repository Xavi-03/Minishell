/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pohernan <pohernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:20:06 by pohernan          #+#    #+#             */
/*   Updated: 2024/11/18 18:29:42 by pohernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_n_strings(char const *s, char c)
{
	size_t	i;
	size_t	n;
	size_t	s_len;
	bool	found;

	i = 0;
	s_len = ft_strlen(s);
	found = false;
	n = 0;
	while (i < s_len)
	{
		if (s[i] == c)
			found = false;
		if (s[i] != c && !found)
		{
			found = true;
			n++;
		}
		i++;
	}
	return (n);
}

static char	*create_substr(const char *s, char c)
{
	size_t	i;
	char	*substr;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	substr = (char *)malloc(sizeof(char) * (i + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s, i + 1);
	return (substr);
}

void	free_substrs(char **strs_arr, size_t n_strs)
{
	size_t	i;

	i = 0;
	while (i < n_strs)
		free(strs_arr[i++]);
}

static char	**fill_strs_arr(char **strs_arr, const char *s, size_t len, char c)
{
	size_t	i;
	size_t	n_strs;
	bool	found;

	i = 0;
	n_strs = 0;
	found = false;
	while (i < len)
	{
		if (s[i] == c)
			found = false;
		if (s[i] != c && !found)
		{
			found = true;
			strs_arr[n_strs] = create_substr(&s[i], c);
			if (!strs_arr[n_strs++])
			{
				free_substrs(strs_arr, --n_strs);
				return (NULL);
			}
		}
		i++;
	}
	strs_arr[n_strs] = NULL;
	return (strs_arr);
}

char	**ft_split(const char *s, char c)
{
	char		**strs_arr;
	int			n_strings;

	n_strings = count_n_strings(s, c);
	strs_arr = (char **)malloc(sizeof(char *) * (n_strings + 1));
	if (!strs_arr || !fill_strs_arr(strs_arr, s, ft_strlen(s), c))
	{
		free(strs_arr);
		return (NULL);
	}
	return (strs_arr);
}
/*
int	main(int argc, char **argv)
{
	char	**split_str;
	size_t	i;

	if (argc != 3)
		return (1);
	split_str = ft_split(argv[1], argv[2][0]);
	i = 0;
	while (i < 4)
	{
		printf("%d: %s\n", i, split_str[i]);
		i++;
	}
	return (0);
}
*/
