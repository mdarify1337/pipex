/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:48:57 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/25 10:20:30 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_printing(char *str, int standard)
{
	ft_putstr_fd(str, standard);
}

void	f_error2(void)
{
	error_printing("-----Command Not Found------\n", ERROR_FD);
	exit(127);
}

void	f_error(t_arg arg)
{
	if (strchr_new(arg.s_cmd[0]) == 1)
	{
		error_printing("-No such file or directory-\n", ERROR_FD);
		exit(127);
	}
	else
	{
		error_printing("-Command--Not---Found-\n", ERROR_FD);
		exit(127);
	}
}

void	f_error3(void)
{
	error_printing("INVALID NUMBER OF ARGUMENTS\n", ERROR_FD);
	exit(1);
}
