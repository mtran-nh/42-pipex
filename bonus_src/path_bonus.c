/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:22:36 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 17:29:29 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
	char	**dirs;
	int		i;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	dirs = ft_split(path_value(envp), ':');
	if (!dirs)
		return (NULL);
	i = -1;
	while (dirs[++i])
	{
		full_path = join_path(dirs[i], cmd);
		if (!full_path)
			return (free_double(dirs), NULL);
		if (!access(full_path, X_OK))
			return (free_double(dirs), full_path);
		free(full_path);
	}
	return (free_double(dirs), NULL);
}
