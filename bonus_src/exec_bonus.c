/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:32:54 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/24 14:20:48 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	execution(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = split_cmd(cmd);
	if (!args || !args[0])
	{
		free_double(args);
		exit_msg("pipex_bonus: failed to split cmds", 127);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex_bonus: command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_double(args);
		exit(127);
	}
	if (execve(path, args, envp) < 0)
	{
		free(path);
		free_double(args);
		exit_msg("pipex_bonus: execve failed", 126);
	}
}

void	child_processes(int fd_in, int fd_out, char *cmd, char **envp)
{
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
		exit_msg("pipex_bonus: dup2 failed", 1);
	close(fd_in);
	close(fd_out);
	execution(cmd, envp);
}

pid_t	create_child(int fd_in, int fd_out, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_msg("pipex: fork failed", 1);
	if (pid == 0)
		child_processes(fd_in, fd_out, cmd, envp);
	return (pid);
}

void	pipe_line(int n, int pipes[][2])
{
	int	i;

	i = -1;
	while (++i < n - 1)
	{
		if (pipe(pipes[i]) < 0)
			exit_msg("pipex_bonus: pipe failed", 1);
	}
}

void	parent_process(int n, char **cmds, char **envp, int in_out[2])
{
	int		(*pipes)[2];
	int		i;
	int		fd_in;

	pipes = malloc(sizeof (int [2]) * (n - 1));
	if (!pipes)
		exit_msg("pipex_bonus: malloc failed", 1);
	pipe_line(n, pipes);
	fd_in = in_out[0];
	i = -1;
	while (++i < n)
	{
		if (i == n - 1)
			create_child(fd_in, in_out[1], cmds[i], envp);
		else
		{
			create_child(fd_in, pipes[i][1], cmds[i], envp);
			close(pipes[i][1]);
			fd_in = pipes[i][0];
		}
	}
	if (fd_in != in_out[0])
		close(fd_in);
	free(pipes);
}
