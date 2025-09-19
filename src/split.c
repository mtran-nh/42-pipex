/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 17:17:44 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/18 18:00:24 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	skip_spaces(char *str, int pos)
{
	while (str[pos] == ' ')
		pos++;
	return (pos);
}

static int	get_arg_length(char *str, int pos, char *quote)
{
	int	start;

	if (str[pos] == '\'' || str[pos] == '"')
	{
		*quote = str[pos++];
		start = pos;
		while (str[pos] && str[pos] != *quote)
			pos++;
		return (pos - start);
	}
	else
	{
		*quote = 0;
		start = pos;
		while (str[pos] && str[pos] != ' ')
			pos++;
		return (pos - start);
	}
}

static int	advance_pos(char *str, int pos, char quote)
{
	if (quote && str[pos] == quote)
		pos++;
	return (pos);
}

static char	*dup_arg(char *str, int pos, int len, char quote)
{
	char	*arg;

	if (quote)
	{
		arg = strndup(str + pos, len);
		if (!arg)
			return (NULL);
	}
	else
	{
		arg = strndup(str + pos, len);
		if (!arg)
			return (NULL);
	}
	return (arg);
}

char	**split_cmd(char *cmd)
{
	char	**args;
	int		arg_index;
	int		pos;
	int		len;
	char	quote;

	arg_index = 0;
	pos = 0;
	if (!cmd)
		return (NULL);
	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);
	while (cmd[pos])
	{
		pos = skip_spaces(cmd, pos);
		if (!cmd[pos])
			break ;
		len = get_arg_length(cmd, pos, &quote);
		args[arg_index++] = dup_arg(cmd, pos, len, quote);
		pos += len;
		pos = advance_pos(cmd, pos, quote);
	}
	args[arg_index] = NULL;
	return (args);
}
