/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:43:01 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 19:07:34 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	wait_children(int n)
{
	int	i;

	i = -1;
	while (++i < n)
		wait(NULL);
}

int	main(int ac, char **av, char **envp)
{
	int		in_out[2];
	int		n_cmds;
	char	**cmds;

	if (ac < 5)
		exit_handle(1);
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		in_out[0] = here_doc(av[2]);
		in_out[1] = open_outfile(av[ac - 1], 1);
		n_cmds = ac - 4;
		cmds = &av[3];
	}
	else
	{
		in_out[0] = open_infile(av[1]);
		in_out[1] = open_outfile(av[ac - 1], 0);
		n_cmds = ac - 3;
		cmds = &av[2];
	}
	parent_process(n_cmds, cmds, envp, in_out);
	close(in_out[0]);
	close(in_out[1]);
	wait_children(n_cmds);
	return (0);
}
