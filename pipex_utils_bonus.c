/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:31:41 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/13 12:34:51 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_unused_pipes(int (*pipes_array)[2], int idx_process)
{
	int	i;

	i = 0;
	while (i <= idx_process)
	{
		if (i != idx_process - 1)
			close(pipes_array[i][0]);
		if (i != idx_process)
			close (pipes_array[i][1]);
		i++;
	}
}

void	close_pipes(int (*pipes_array)[2], int array_length)
{
	int	i;

	i = 0;
	while (i < array_length)
	{
		close(pipes_array[i][1]);
		close(pipes_array[i][0]);
		i++;
	}
}

void	wait_for_childs(int *p_ids, int commands_number)
{
	int	i;
	int	status;
	int	_exit;

	status = 0;
	_exit = 0;
	i = 0;
	while (i < commands_number)
		waitpid(p_ids[i++], &status, 0);
	if (WIFEXITED(status))
		_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		_exit = WTERMSIG(status) + 128;
	exit(_exit);
}

void	duplicating(int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
}

int	get_input_lines(char *limiter)
{
	char	*last;
	int		hidden_file_fd;

	last = get_next_line(0);
	unlink(HIDDEN_FILE);
	hidden_file_fd = open(HIDDEN_FILE, O_WRONLY | O_CREAT, FULL_ACCESS);
	while (last)
	{
		if (ft_strncmp(last, limiter, ft_strlen(limiter)) == 0)
			if (last[ft_strlen(limiter)] == '\n')
				break ;
		ft_putstr_fd(last, hidden_file_fd);
		ft_putstr_fd("\n", hidden_file_fd);
		free(last);
		last = get_next_line(0);
	}
	free(last);
	close(hidden_file_fd);
	open(HIDDEN_FILE, O_RDONLY, FULL_ACCESS);
	return (hidden_file_fd);
}