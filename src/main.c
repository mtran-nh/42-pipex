/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:40:17 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/12 19:55:04 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		exit_error("failed to open infile", NULL);
	return (fd);
}

int	open_outfile(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("outfile", NULL);
	return (fd);
}

void	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		exit_error("pipe", NULL);
}

pid_t	create_child(void (*child_func)(int, int *, char *, char **), int file,
		int fd[2], char *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
		child_func(file, fd, cmd, envp);
	return (pid);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
	int		exitcode;

	exitcode = 1;
	if (ac != 5)
		return (fprintf(stderr, "Usage:%s infile cmd1 cmd2 outfile\n", av[0]),
			1);
	infile = open_infile(av[1]);
	outfile = open_outfile(av[4]);
	create_pipe(fd);
	pid1 = create_child(child_process1, infile, fd, av[2], envp);
	pid2 = create_child(child_process2, outfile, fd, av[3], envp);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, &status1, 0);
	if (waitpid(pid2, &status2, 0) > 0 && WIFEXITED(status2))
		exitcode = WEXITSTATUS(status2);
	return (exitcode);
}
