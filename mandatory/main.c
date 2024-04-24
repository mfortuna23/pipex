/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/24 14:39:28 by mfortuna         ###   ########.fr       */
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
