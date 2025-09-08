/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:38 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/08 14:02:43 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
