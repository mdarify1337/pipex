/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:30:52 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/06 17:35:39 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_quotes_replacing(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'')
		{
			replacing(command + i + 1, ' ', -1);
			break ;
		}
		i++;
	}
	return (command);
}

void	replacing(char *s, char to_be_replaced, char replacer)
{
	int	i;

	i = 0;
	while (s[i] != '\'')
	{
		if (s[i] == to_be_replaced)
			s[i] = replacer;
		i++;
	}
}