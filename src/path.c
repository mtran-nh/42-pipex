/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 19:48:02 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/06 19:59:57 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *path_value(char **envp)
{
	int i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		return (NULL);
	}
}

char *get_cmd_path(char *cmd, char **envp)
{
	char *path = path_value(envp);
	if (!path)
		return (NULL);
	char *dup = ft_strdup(path);
	if (!dup)
		retun (NULL);
	char *cmds = ft_split(dup, ":");
	while (cmds)
}