/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:48:02 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/13 19:26:44 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*path_value(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	int		i;
	char	*full_path;

	path = path_value(envp);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs[++i])
	{
		full_path = join_path(dirs[i], cmd);
		if (!full_path)
			return (free_arr(dirs), NULL);
		if (!access(full_path, X_OK))
			return (free_arr(dirs), full_path);
		free(full_path);
	}
	return (free_arr(dirs), NULL);
}

char	**split_cmd(char *cmd)
{
	char	**args;

	if (!cmd)
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
		return (NULL);
	return (args);
}
