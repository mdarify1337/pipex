/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:10:23 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/25 10:20:14 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	executing_command(char **av, char **env_variables, int arg_position)
{
	char	*quotes_handling;
	t_arg	arg;
	int		i;

	i = 0;
	quotes_handling = NULL;
	if (ft_strlen(av[arg_position]) == 0)
		f_error2();
	quotes_handling = find_quotes_replacing(av[arg_position]);
	arg.s_cmd = ft_split(quotes_handling, ' ');
	while (arg.s_cmd[i])
	{
		if (arg.s_cmd[i][0] == '\'')
		{
			replacing(arg.s_cmd[i] + 1, -1, ' ');
			arg.s_cmd[i] = ft_substr(arg.s_cmd[i], 1, ft_strlen(arg.s_cmd[i])
					- 2);
		}
		i++;
	}
	arg.full_path = get_command_path(env_variables, arg.s_cmd[0]);
	if (execve(arg.full_path, arg.s_cmd, env_variables) == -1)
		f_error(arg);
}

void	getting_things_ready(t_process_vars *vars, char **av, int ac)
{
	(void)av;
	vars->command_number = ac - 3;
	vars->p_ids = malloc(sizeof(int) * vars->command_number);
	vars->first_command_position = 2;
	vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
	vars->pipes_number = vars->command_number - 1;
	vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
}

void	getting_things_ready2(t_process_vars *vars, char **av, int ac)
{
	(void)av;
	vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, FULL_ACCESS);
	if (vars->output_fd < 0)
	{
		if (vars->input_fd < 0)
		{
			error_printing("-no such file or directory-\n", ERROR_FD);
		}
		perror("cmd");
	}
	vars->pipes_number = vars->command_number - 1;
	vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
}

void	pipe_simulating(t_process_vars *vars, char **av, char **env_variables,
		int index)
{
	if (vars->p_ids[index] == 0)
	{
		close_unused_pipes(vars->pipes_array, index);
		if (index == 0)
		{
			if (vars->input_fd < 0)
			{
				error_printing("-----no such file or directory\n", OUTPUT_FD);
				exit(127);
			}
			duplicating(vars->input_fd, vars->pipes_array[index][1]);
		}
		else if (index == vars->command_number - 1)
			duplicating(vars->pipes_array[index - 1][INPUT_FD],
				vars->output_fd);
		else
			duplicating(vars->pipes_array[index - 1][INPUT_FD],
				vars->pipes_array[index][OUTPUT_FD]);
		executing_command(av, env_variables, (index
				+ vars->first_command_position));
	}
}

int	main(int ac, char **av, char **env_variables)
{
	t_process_vars	vars;
	int				i;

	i = 0;
	if (ac != 5)
		f_error3();
	getting_things_ready(&vars, av, ac);
	getting_things_ready2(&vars, av, ac);
	while (i < vars.command_number)
	{
		if ((i == 0 && vars.input_fd < 0) || (i == vars.command_number - 1
				&& vars.output_fd < 0))
		{
			i++;
			continue ;
		}
		pipe(vars.pipes_array[i]);
		vars.p_ids[i] = fork();
		pipe_simulating(&vars, av, env_variables, i);
		i++;
	}
	close_pipes(vars.pipes_array, vars.pipes_number);
	wait_for_childs(vars.p_ids, vars.command_number);
	close(vars.input_fd);
	close(vars.output_fd);
}
