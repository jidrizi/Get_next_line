/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jidrizi <jidrizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:20:11 by jidrizi           #+#    #+#             */
/*   Updated: 2024/05/22 19:20:13 by jidrizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*streng;
	size_t			x;

	streng = (unsigned char *)s;
	x = 0;
	while (x < n)
	{
		streng[x] = '\0';
		x++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		x;
	char	*fun;

	x = ft_strlen(s1) + ft_strlen(s2) + 1;
	fun = malloc(x * sizeof(char));
	if (!fun && s1)
		return (free(s1), NULL);
	if (!fun)
		return (NULL);
	ft_bzero(fun, x * sizeof(char));
	if (s1)
		ft_strlcpy(fun, s1, x);
	if (s2)
		ft_strlcat(fun, s2, x);
	if (s1)
		free(s1);
	return (fun);
}

static char	*ft_read_until_new_line_or_eof(char *sstring, int fd, int error)
{
	char	*r_line;

	r_line = NULL;
	if (*sstring == '\0')
		error = read(fd, sstring, BUFFER_SIZE);
	if (error < 1)
		return (NULL);
	while (*sstring && !(ft_strchr(sstring, '\n') || error < BUFFER_SIZE))
	{
		r_line = ft_strjoin(r_line, sstring);
		if (r_line == NULL)
			return ((void *)1);
		ft_bzero(sstring, BUFFER_SIZE + 1);
		error = read(fd, sstring, BUFFER_SIZE);
		if (r_line && error < 0)
			return (free (r_line), NULL);
		if (error < 0)
			return (NULL);
	}
	return (r_line);
}

char	*get_next_line(int fd)
{
	static char	sstring[BUFFER_SIZE + 1];
	char		*new_line;
	char		*r_line;

	r_line = ft_read_until_new_line_or_eof(sstring, fd, BUFFER_SIZE);
	if (r_line == (void *)1)
		return (ft_bzero(sstring, BUFFER_SIZE), NULL);
	if (*sstring == 0 && r_line == NULL)
		return (NULL);
	new_line = ft_strchr(sstring, '\n');
	if (new_line != NULL)
		*new_line = '\0';
	r_line = ft_strjoin(r_line, sstring);
	if (r_line == NULL)
		return (NULL);
	if (new_line != NULL)
		r_line = ft_strjoin(r_line, "\n");
	if (r_line == NULL)
		return (NULL);
	if (new_line != NULL && new_line[1] != '\0')
		ft_strlcpy(sstring, new_line + 1, ft_strlen(new_line + 1) + 1);
	else
		ft_bzero(sstring, BUFFER_SIZE + 1);
	return (r_line);
}

// #ifdef DBUG

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("a", O_RDONLY);
// 	for (int i = 0; i < 2; i++)
// 	{
// 		str = get_next_line(fd);
// 		printf("<Line %i>%s\n", i, str);
// 		free(str);
// 	}
// 	return (0);
// }
// #endif
