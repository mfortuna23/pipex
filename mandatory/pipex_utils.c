/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:25:11 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/08 19:02:32 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clean(int n_fd, int **fd)
{
	int	i;

	i = 0;
	ft_close_files(fd, n_fd);
	while (i < n_fd)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

int	**ft_pipe_fds(int n_fd)
{
	int	i;
	int	**fd;

	i = 0;
	fd = ft_calloc(n_fd + 1, sizeof(int *));
	if (!fd)
		exit (5);
	while (i <= n_fd)
	{
		fd[i] = ft_calloc(3, sizeof(int));
		if (!fd[i])
		{
			ft_clean(n_fd, fd);
			ft_printf("Error creating fd");
			exit (1);
		}
		if (pipe(fd[i]) == 1)
		{
			ft_clean(n_fd, fd);
			ft_printf("Error creating pipe");
			exit (1);
		}
		i++;
	}
	return (fd);
}

void	ft_close_files(int **fd, int n_fds)
{
	int	i;

	i = 0;
	while (i <= n_fds)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	ft_clean_proc(int n_fd, int **fd, int *pid)
{
	ft_clean(n_fd, fd);
	free(pid);
	ft_printf("an error happend creating child process");
	exit(2);
}