/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:10:23 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/21 10:24:31 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int strchr_new(char *str)
{
	int l;

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

char *get_command_path(char **env_variables, char *command)
{
	char *full_path;
	int i;

	i = -1;
	if (strchr_new(command) && access(command, F_OK & X_OK))
		return (command);
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH=", 5) == 0)
			break;
	}
	if (env_variables[i] != NULL)
		env_variables = ft_split(env_variables[i], ':');
	i = -1;
	while (env_variables && env_variables[++i])
	{
		full_path = ft_strjoin(ft_strjoin(env_variables[i], "/"), command);
		if (access(full_path, F_OK & X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (command);
}

void f_error(char	)
{
	t_arg	arg;

	if (strchr_new(arg.splited_command))
	{
		fprintf(stderr, "%s", "hello");
		fprintf(stderr, "%s", arg.splited_command);
		perror("INVALID--FULL-PATH : ");
		exit(127);
	}
	else
		error_printing("----Command Not Found----\n", ERROR_FD);
}

void executing_command(char **av, char **env_variables, int arg_position)
{
	char *quotes_handling;
	t_arg arg;
	int i;

	i = 0;
	quotes_handling = NULL;
	if (ft_strlen(av[arg_position]) == 0)
		error_printing("------Command Not Found----\n", ERROR_FD);
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
			f_error();
}

void getting_things_ready(t_process_vars *vars, char **av, int ac)
{
	(void)av;
	vars->command_number = ac - 3;
	vars->p_ids = malloc(sizeof(int) * vars->command_number);
	vars->first_command_position = 2;
	vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
	vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, FULL_ACCESS);
	if (vars->output_fd < 0)
	{
		perror("");
		exit(1);
	}
	vars->pipes_number = vars->command_number - 1;
	vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
}

void pipe_simulating(t_process_vars *vars, char **av, char **env_variables,
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
		executing_command(av, env_variables, (index + vars->first_command_position));
	}
}

int main(int ac, char **av, char **env_variables)
{
	t_process_vars vars;
	int i;

	i = 0;
	if (ac != 5)
	{
		write(2, "ERROR: Invalid Number of arguments", 35);
		exit(1);
	}
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
	system("leaks pipex");
	close(vars.input_fd);
	close(vars.output_fd);
}
