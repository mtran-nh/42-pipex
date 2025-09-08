/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:31 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/08 19:06:51 by mtran-nh         ###   ########.fr       */
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
