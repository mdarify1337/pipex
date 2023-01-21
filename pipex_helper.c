/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:37:28 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/21 09:15:48 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_unused_pipes(int (*pipes_array)[2], int idx_process)
{
	int	i;

	i = -1;
	while (++i <= idx_process)
	{
		if (i != idx_process - 1)
			close(pipes_array[i][0]);
		// fprintf(stderr, "%s", "hello");
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
