/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:13:54 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/17 13:03:23 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_double(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	exit_handle(int ex)
{
	if (ex == 1)
		ft_putstr_fd("input: ./program infile cmd1 cmd2 outfile\n", 2);
	exit(0);
}

// 0 for infile
// 1 for outfile
int	open_file(char *file, int n)
{
	int	check_open;

	if (n == 0)
		check_open = open(file, O_RDONLY);
	if (n == 1)
		check_open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (check_open == -1)
		exit(0);
	return (check_open);
}
