/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:40:17 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/13 17:34:55 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	init_pipex(int *infile, int *outfile, int fd[2],
		const char *infile_name, const char *outfile_name)
{
	*infile = open(infile_name, O_RDONLY);
	if (*infile < 0)
		exit_error("failed to open infile", NULL);
	*outfile = open(outfile_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		close(*infile);
		exit_error("failed to open outfile", NULL);
	}
	if (pipe(fd) == -1)
	{
		close(*infile);
		close(*outfile);
		exit_error("pipe failed", NULL);
	}
}

static pid_t	create_child(void (*child_func)(int, int *, char *, char **),
		int file, int fd[2], char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork failed", NULL);
	if (pid == 0)
		child_func(file, fd, cmd, NULL); // truyền envp khác cách khác nếu cần
	return (pid);
}

static int	run_pipex(int infile, int outfile, int fd[2], char **av,
		char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		exitcode;

	pid1 = create_child(child_process1, infile, fd, av[2], envp);
	pid2 = create_child(child_process2, outfile, fd, av[3], envp);
	int status1, status2;
	exitcode = 1;
	close(fd[0]);
	close(fd[1]);
	close(infile);
	close(outfile);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		exitcode = WEXITSTATUS(status2);
	return (exitcode);
}

int	main(int ac, char **av, char **envp)
{
	int fd[2], infile, outfile;
	if (ac != 5)
		return (fprintf(stderr, "Usage: %s infile cmd1 cmd2 outfile\n", av[0]),
			1);
	init_pipex(&infile, &outfile, fd, av[1], av[4]);
	return (run_pipex(infile, outfile, fd, av, envp));
}
