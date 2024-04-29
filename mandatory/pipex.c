/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/29 11:45:23 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	permissions(char *s, int amode)
{
	if (access(s, F_OK) == 0)
	{
		if (access(s, amode) == 0)
			return (0);
		perror(s);
		return (1);
	}
	else
	{
		perror(s);
		return (1);
	}
}

static char	*find_path(char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 1;
	full_path = NULL;
	paths[0] = "/bin/";
	paths[1] = "/usr/bin/";
	paths[2] = "/usr/local/bin/";
	full_path = ft_strjoin(paths[0], cmd);
	while (access(full_path, X_OK) != 0)
	{
		if (i == 3)
		{
			ft_printf("command %s not found", cmd);
			free(full_path);
			return (NULL);
		}
		full_path = ft_strjoin(paths[i], cmd);
		i++;
	}
	return (full_path);
}

static int	parent_proc(char **argv, int fd);

static int	child_proc(char **argv, int fd);

int	main(int argc, char **argv)
{
	int	fd[2];
	int	id;

	if (argc == 5)
	{
		if (permissions(argv[1], R_OK) == 1)
			return (1);
		if (pipe(fd) == -1)
			return (ft_printf("Error creating a pipe \n"));
		id = fork();
		if (id == 0)
			child_proc(argv, fd);
		else
			parent_proc(argv, fd);
		close(fd[0]);
		close(fd[1]);
	}
	return (1);
}
