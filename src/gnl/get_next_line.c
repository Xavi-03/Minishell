/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtinaut- <jtinaut-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:56:56 by jtinaut-          #+#    #+#             */
/*   Updated: 2024/10/10 19:13:44 by jtinaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_line;
	t_gnl		*list;
	t_gnl		*iteri;

	list = NULL;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (buffer)
		ft_addnode(&list, buffer);
	iteri = list;
	while (!iteri || !ft_ft_strchr(iteri->text))
	{
		iteri = ft_addnode(&list, ft_reader(fd));
		if (!iteri)
		{
			if (list)
				break ;
			return (NULL);
		}
	}
	new_line = ft_injector(&list, &buffer);
	return (ft_trimmer(new_line));
}

char	*ft_injector(t_gnl **list, char **buffer)
{
	char	*new_line;
	t_gnl	*iteri;

	iteri = *list;
	if (ft_memorymanager((void *)&new_line, (ft_listlen(*list) * BUFFER_SIZE)))
		return (NULL);
	if (ft_memorymanager((void **)&*buffer, BUFFER_SIZE))
		return (NULL);
	new_line[0] = '\0';
	while (iteri)
	{
		ft_strcpy(*buffer, ft_strcpy(new_line, iteri->text));
		iteri = iteri->next;
	}
	if (**buffer == '\0')
	{
		free(*buffer);
		*buffer = NULL;
	}
	ft_memorymanager((void **)&*list, 0);
	return (new_line);
}

char	*ft_reader(int fd)
{
	char	*new_line;
	int		readed;

	if (ft_memorymanager((void *)&new_line, BUFFER_SIZE))
		return (NULL);
	readed = read(fd, new_line, BUFFER_SIZE);
	if (readed < 1)
	{
		free(new_line);
		return (NULL);
	}
	new_line[BUFFER_SIZE] = '\0';
	return (new_line);
}

int	ft_memorymanager(void **value, int size)
{
	int		i;
	t_gnl	*iteri;

	if (size == 0)
	{
		while (*value)
		{
			iteri = *(t_gnl **)value;
			*(t_gnl **)value = iteri->next;
			free(iteri->text);
			free(iteri);
		}
		return (0);
	}
	i = 0;
	*value = malloc((size + 1) * sizeof(char));
	if (!*value)
		return (1);
	while (i < size)
	{
		((char *)*value)[i] = '\0';
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*next_line;
	int		fd;
	//int		fd2;
	int		i;

	i = 1;
	if (argc > 1)
	{
		fd = open(argv[i], O_RDONLY);
		//fd2 = open("test", O_RDONLY);
		while (i < 20)
		{
			next_line = get_next_line(0);
			printf("\nMain new line:%s$\n______________________\n\n", next_line);
			if (!next_line)
				break ;
			free(next_line);
			i++;
		}
		close(fd);
	}
	return (0);
}
*/
