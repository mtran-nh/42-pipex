/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:53:43 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/24 14:23:34 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

void	free_double(char **arr);
void	exit_handle(char *msg, int ex);
int		open_file(char *file, int n);

char	**split_cmd(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

void	execution(char *cmd, char **envp);
void	child_process1(int in_out[2], int p_fd[2], char *cmd, char **envp);
void	child_process2(int in_out[2], int p_fd[2], char *cmd, char **envp);
int		main(int ac, char **av, char **envp);
#endif