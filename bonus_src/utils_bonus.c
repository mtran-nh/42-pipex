/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:48:07 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 19:00:52 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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
		ft_putstr_fd("input: ./pipex_bonus infile cmd1 ... cmdn outfile\n", 2);
	exit(1);
}

int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("pipex_bonus: No such file or directory: ", 2);
		ft_putendl_fd(file, 2);
		fd = open("/dev/null", O_RDONLY);
	}
	return (fd);
}

int	open_outfile(char *file, int append)
{
	int	fd;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("pipex_bonus: cannot open outfile: ", 2);
		ft_putendl_fd(file, 2);
		exit(1);
	}
	return (fd);
}

int	here_doc(char *limiter)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}
