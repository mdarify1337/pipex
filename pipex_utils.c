/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:36:47 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/25 10:20:37 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	strchr_new(char *str)
{
	int	l;

	l = 0;
	if (!str)
		return (0);
	while (str[l])
	{
		if (str[l] == '/')
			return (1);
		l++;
	}
	return (0);
}

char	*get_command_path(char **env_variables, char *command)
{
	char	*full_path;
	char	**path;
	int		i;

	i = -1;
	if (strchr_new(command) && access(command, F_OK & X_OK))
		return (command);
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
			break ;
	}
	path = ft_split(env_variables[i], ':');
	i = -1;
	while (path && path[++i])
	{
		full_path = ft_strjoin(ft_strjoin(path[i], "/"), command);
		if (access(full_path, F_OK & X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (command);
}
