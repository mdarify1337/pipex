/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:57:49 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/08 11:29:28 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	word_counter(char const *s, char sep)
{
	int	index_word;
	int	m;

	index_word = 0;
	m = 0;
	while (s[m])
	{
		while (s[m] && s[m] == sep)
			m++;
		if (s[m] && s[m] != sep)
			index_word++;
		while (s[m] && s[m] != sep)
			m++;
	}
	return (index_word);
}

char	*diviser_src(char const *s, int i, int k)
{
	char	*current;
	int		m;

	current = (char *)malloc(sizeof(char) * (k - i + 1));
	if (!current)
		return (NULL);
	m = 0;
	while (s[i] != '\0' && i < k)
	{
		current[m] = s[i];
		m++;
		i++;
	}
	current[m] = 0;
	return (current);
}

void	ft_free(char **s, int m)
{
	int	i;

	i = 0;
	while (i <= m)
	{
		free(s[m]);
		i++;
	}
	free(s);
}

char	**ft_fill(char **accumulator, char const *s, char sep)
{
	int	m;
	int	i;
	int	k;

	m = 0;
	i = 0;
	while (s[i] && m < word_counter(s, sep))
	{
		while (s[i] && s[i] == sep)
			i++;
		k = i;
		while (s[i] && s[i] != sep)
			i++;
		accumulator[m] = diviser_src(s, k, i);
		if (!accumulator[m])
		{
			ft_free(accumulator, m);
			return (NULL);
		}
		m++;
	}
	accumulator[m] = NULL;
	return (accumulator);
}

char	**ft_split(char *s, char c)
{
	char	**accumulator;

	if (!s)
		return (0);
	accumulator = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!accumulator)
		return (NULL);
	if (!ft_fill(accumulator, s, c))
		return (NULL);
	return (accumulator);
}
