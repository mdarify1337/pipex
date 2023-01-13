/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:06:18 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/13 12:39:30 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	error_printing(char *str, int standard)
{
	ft_putstr_fd(str, standard);
	exit(1);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int ft_strncmp(char *s2, char *s1, size_t len)
{
	unsigned char	*src;
	unsigned char	*dst;
	size_t			i;

	src = (unsigned char *)s1;
	dst = (unsigned char *)s2;
	i = 0;
	while (i < len && (src[i] || dst[i]))
	{
		if (src[i] != dst[i])
			return (dst[i] - src[i]);
		i++;
	}
	return (0);
}
