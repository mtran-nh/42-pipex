/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:31 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/17 13:33:10 by mtran-nh         ###   ########.fr       */
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
		ft_putendl_fd ("failed to split cmds", 2);
		free_double (args);
		exit (1);
	}
	path = get_cmd_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd ("command not found: ", 2);
		ft_putendl_fd (args[0], 2);
		free_double (args);
		exit (127);
	}
	if (execve(path, args, envp) < 0)
	{
		free(path);
		free_double (args);
		ft_putendl_fd ("execve failed", 2);
		exit (126);
	}
}

void	child_process(int in_fd, int out_fd, char *cmd, char **envp)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror ("dup2 input");
		exit (1);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror ("dup2 output");
		exit (1);
	}
	execution(cmd, envp);
}
