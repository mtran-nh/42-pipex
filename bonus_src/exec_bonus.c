/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:32:54 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 18:54:18 by mtran-nh         ###   ########.fr       */
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
		ft_putendl_fd("pipex_bonus: failed to split cmds", 2);
		free_double(args);
		exit(127);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("pipex_bonus: command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		free_double(args);
		exit(127);
	}
	if (execve(path, args, envp) < 0)
	{
		ft_putendl_fd("pipex_bonus: execve failed", 2);
		free(path);
		free_double(args);
		exit(126);
	}
}

void	child_processes(int fd_in, int fd_out, char *cmd, char **envp)
{
	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
	{
		ft_putendl_fd("pipex_bonus: dup2 failed", 2);
		exit(1);
	}
	close(fd_in);
	close(fd_out);
	execution(cmd, envp);
}

pid_t	create_child(int fd_in, int fd_out, char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("pipex: fork failed", 2);
		exit(1);
	}
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
		{
			ft_putendl_fd("pipex_bonus: pipe failed", 2);
			exit(1);
		}
	}
}

void	parent_process(int n, char **cmds, char **envp, int in_out[2])
{
	int		pipes[n - 1][2];
	int		i;
	int		fd[2];

	pipe_line(n, pipes);
	i = -1;
	while (++i < n)
	{
		if (i == 0)
			fd[0] = in_out[0];
		else
			fd[0] = pipes[i - 1][0];
		if (i == n - 1)
			fd[1] = in_out[1];
		else
			fd[1] = pipes[i][1];
		create_child(fd[0], fd[1], cmds[i], envp);
		if (i > 0)
			close(pipes[i - 1][0]);
		if (i < n - 1)
			close(pipes[i][1]);
	}
}
