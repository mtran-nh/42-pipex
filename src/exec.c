/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:31 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/24 14:37:22 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execution(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = split_cmd(cmd);
	if (!args || !args[0])
	{
		free_double(args);
		exit_handle("pipex: failed to split cmds", 127);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_double(args);
		exit(127);
	}
	if (execve(path, args, envp) < 0)
	{
		ft_putendl_fd("pipex: execve failed", 2);
		free(path);
		free_double(args);
		exit_handle("pipex: execve failed", 126);
	}
}

void	child_process1(int in_out[2], int p_fd[2], char *cmd, char **envp)
{
	close(p_fd[0]);
	close(in_out[1]);
	if (dup2(in_out[0], STDIN_FILENO) < 0 || dup2(p_fd[1], STDOUT_FILENO) < 0)
		exit_handle("pipex: dup2 failed", 1);
	close(in_out[0]);
	close(p_fd[1]);
	execution(cmd, envp);
}

void	child_process2(int in_out[2], int p_fd[2], char *cmd, char **envp)
{
	close(p_fd[1]);
	close(in_out[0]);
	if (dup2(p_fd[0], STDIN_FILENO) < 0 || dup2(in_out[1], STDOUT_FILENO) < 0)
		exit_handle("pipex: dup2 failed", 1);
	close(in_out[1]);
	close(p_fd[0]);
	execution(cmd, envp);
}
