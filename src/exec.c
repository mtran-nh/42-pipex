/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:31 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/09 17:32:19 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execution(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = split_cmd(cmd);
	if (!args || !args[0])
		exit_error("failed to split cmd", args);
	path = get_cmd_path(args[0], envp);
	if (!path)
		exit_error("command not found", args);
	if (execve(path, args, envp) < 0)
	{
		free(path);
		exit_error("execve failed", args);
	}
}

void	child_process1(int infile, int fd[2], char *cmd, char **envp)
{
	if (dup2(infile, STDIN_FILENO) < 0)
		exit_error("dup2 infile failed");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		exit_error("dup2 pipe write failed");
	close (fd[0]);
	close (fd[1]);
	close (infile);
	execution(cmd, envp);
}

void	child_process2(int outfile, int fd[2], char *cmd, char **envp)
{
	if (dup2(fd[0], STDIN_FILENO) < 0)
		exit_error("dup2 pipe out failed");
	if (dup2(outfile, STDOUT_FILENO) < 0)
		exit_error("dup2 outfile failed");
	close (fd[0]);
	close (fd[1]);
	close (outfile);
	execution (cmd, envp);
}
