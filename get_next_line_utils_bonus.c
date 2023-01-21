/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 21:29:03 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/21 06:28:03 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	strchr_newline(char *str)
{
	int	l;

	l = 0;
	if (!str)
		return (0);
	while (str[l])
	{
		if (str[l] == '\n')
			return (1);
		l++;
	}
	return (0);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (start + len >= ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (&str[0]);
	}
	if (len >= ft_strlen(s))
		str = malloc(ft_strlen(s) + 1);
	else
		str = malloc(len + 1);
	if (!str)
		return (0);
	while (s[i] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strcat(char *pdf, char *dest, char *src)
{
	int	m;
	int	n;
	int	j;

	m = 0;
	n = 0;
	j = 0;
	while (dest[m] != '\0')
	{
		pdf[j] = dest[m];
		m++;
		j++;
	}
	while (src[n] != '\0')
	{
		pdf[j + n] = src[n];
		n++;
	}
	pdf[j + n] = '\0';
	return (pdf);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s_index;
	int		z_index;
	char	*pdf;

	if (!s1)
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	s_index = ft_strlen(s1);
	z_index = ft_strlen(s2) + 1;
	pdf = (char *)malloc((s_index + z_index) * sizeof(char));
	if (!pdf)
	{
		free(s1);
		return (NULL);
	}
	pdf = ft_strcat(pdf, s1, s2);
	// free(s1);
	return (pdf);
}
