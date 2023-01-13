/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:10:20 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/10 19:57:55 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command_path(char **env_var, char *command)
{
	char	*full_path;
	int		i;

	i = -1;
	while (env_var[++i])
	{
		if (env_var[i] != NULL && ft_strncmp(env_var[i], "PATH=", 5) == 0)
			break ;
	}
	env_var = ft_split(env_var[i], ':');
	if (env_var == NULL)
		write(2, "ERROR :", 7);
	i = -1;	
	while (env_var[++i])
	{
		full_path = ft_strjoin(env_var[i], "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, F_OK & X_OK) == 0)
		{
			printf("%s\n", full_path);
			return (full_path);
		}
	}
	perror("INVALID :");
		exit(127);
	return (command);
}

void	executing_command(char **av, char **env_variables, int arg_position)
{
	char	*quotes_handling;
	t_arg	arg;
	int		i;

	i = 0;
	quotes_handling = NULL;
	if (ft_strlen(av[arg_position]) == 0)
		error_printing("Command Not Found\n", ERROR_FD);
	quotes_handling = find_quotes_replacing(av[arg_position]);
	arg.splited_command = ft_split(quotes_handling, ' ');
	while (arg.splited_command[i])
	{
		if (arg.splited_command[i][0] == '\'')
		{
			replacing(arg.splited_command[i] + 1, -1, ' ');
			arg.splited_command[i] = ft_substr(arg.splited_command[i], 1,
					ft_strlen(arg.splited_command[i]) - 2);
		}
		i++;
	}
	arg.full_path = get_command_path(env_variables, arg.splited_command[0]);
	if (execve(arg.full_path, arg.splited_command, env_variables) == -1)
		error_printing("Command Not Found\n", ERROR_FD);
}

void	getting_things_ready(t_process_vars *vars, char **av, int ac)
{
	vars->command_number = ac - 3;
	vars->p_ids = malloc(sizeof(int) * vars->command_number);
	vars->first_command_position = 2;
	if (ft_strcmp(av[FIRST_FILE_ARG], HERE_DOC) == 0)
	{
		vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND,
				FULL_ACCESS);
		vars->input_fd = get_input_lines(av[2]);
		vars->command_number--;
		vars->first_command_position++;
	}
	else
	{
		vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
		vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC,
				FULL_ACCESS);
	}
	if (vars->output_fd < 0)
	{
		perror("");
		exit(1);
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
				error_printing("no such file or directory\n", OUTPUT_FD);
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
	getting_things_ready(&vars, av, ac);
	while (i < vars.command_number)
	{
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
