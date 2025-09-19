/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:40:17 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/18 17:26:48 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static pid_t	create_child1(int in_out[2], int p_fd[2], char *cmd,
		char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("pipex: fork failed", 2);
		exit(1);
	}
	if (pid == 0)
	{
		close(p_fd[0]);
		child_process1(in_out, p_fd, cmd, envp);
	}
	return (pid);
}

static pid_t	create_child2(int in_out[2], int p_fd[2], char *cmd,
		char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("pipex: fork failed", 2);
		exit(1);
	}
	if (pid == 0)
	{
		close(p_fd[1]);
		child_process2(in_out, p_fd, cmd, envp);
	}
	return (pid);
}

int	main(int ac, char **av, char **envp)
{
	int		p_fd[2];
	int		in_out[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (ac != 5)
		exit_handle(1);
	in_out[0] = open_file(av[1], 0);
	in_out[1] = open_file(av[4], 1);
	if (pipe(p_fd) == -1)
		return (ft_putendl_fd("pipex: pipe failed", 2), 1);
	pid1 = create_child1(in_out, p_fd, av[2], envp);
	pid2 = create_child2(in_out, p_fd, av[3], envp);
	close(p_fd[0]);
	close(p_fd[1]);
	close(in_out[0]);
	close(in_out[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
