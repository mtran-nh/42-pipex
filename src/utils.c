/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 17:13:54 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 14:00:38 by mtran-nh         ###   ########.fr       */
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
		ft_putstr_fd("input: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(1);
}

// 0 for infile
// 1 for outfile
int	open_file(char *file, int n)
{
	int	check_open;

	if (n == 0)
	{
		check_open = open(file, O_RDONLY);
		if (check_open == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd("No such file or directory: ", 2);
			ft_putendl_fd(file, 2);
			check_open = open("/dev/null", O_RDONLY);
		}
	}
	else
	{
		check_open = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (check_open == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(file, 2);
			ft_putendl_fd(": cannot open", 2);
			exit(1);
		}
	}
	return (check_open);
}
