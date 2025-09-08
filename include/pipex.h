/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:53:43 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/08 19:02:05 by mtran-nh         ###   ########.fr       */
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

void	free_arr(char **arr);
void	exit_error(const char *msg, char **need_free);
char	**split_cmd(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

#endif