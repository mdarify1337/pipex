/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:02:08 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/25 11:00:49 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define INPUT_FD 0
# define OUTPUT_FD 1
# define ERROR_FD 2
# define FIRST_FILE_ARG 1
# define FULL_ACCESS 0777
# define HIDDEN_FILE "/tmp/.temp_file"
# define HERE_DOC "here_doc"

typedef struct s_variables
{
	int		*p_ids;
	int		(*pipes_array)[2];
	int		input_fd;
	int		output_fd;
	int		command_number;
	int		pipes_number;
	int		first_command_position;
}			t_process_vars;
typedef struct argument
{
	char	**s_cmd;
	char	*full_path;
}			t_arg;

void		f_error3(void);
void		f_error2(void);
void		f_error(t_arg arg);
int			ft_strchr_new2(char *str);
int			strchr_new(char *str);
size_t		ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char *s, char c);
void		error_printing(char *str, int standard);
char		*get_next_line(int fd);
int			ft_strcmp(char *s2, char *s1);
int			ft_strncmp(char *s2, char *s1, size_t len);
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*find_quotes_replacing(char *command);
void		replacing(char *s, char to_be_replaced, char replacer);
char		*get_command_path(char **env_var, char *command);
void		executing_command(char **av, char **env_variables,
				int arg_position);
void		getting_things_ready(t_process_vars *vars, char **av, int ac);
void		close_unused_pipes(int (*pipes_array)[2], int idx_process);
void		close_pipes(int (*pipes_array)[2], int array_length);
void		wait_for_childs(int *p_ids, int commands_number);
void		duplicating(int input, int output);
int			get_input_lines(char *limiter);
void		pipe_simulating(t_process_vars *vars, char **av,
				char **env_variables, int index);

#endif
