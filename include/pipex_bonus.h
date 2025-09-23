/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:44:10 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 19:06:37 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	free_double(char **arr);
void	exit_handle(int ex);
int		open_infile(char *file);
int		open_outfile(char *file, int append);
int	    here_doc(char *limiter);

char	*get_next_line(int fd);

char	*get_cmd_path(char *cmd, char **envp);
char	**split_cmd(char *cmd);

void	execution(char *cmd, char **envp);
void	child_processes(int fd_in, int fd_out, char *cmd, char **envp);
pid_t	create_child(int fd_in, int fd_out, char *cmd, char **envp);
void	pipe_line(int n, int pipes[][2]);
void	parent_process(int n, char **cmds, char **envp, int in_out[2]);

int		main(int ac, char **av, char **envp);
#endif