/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/13 10:58:08 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pipe(char **argv, char **env, int fd_in, int fd_out)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		errors("pipe");
	pid = fork();
	if (pid < 0)
		errors("fork");
	if (pid == 0)
	{
		close(fd[0]);
		ft_cp(argv[2], env, fd_in, fd[1]);
	}
	ft_wait(pid, fd[1]);
	pid = fork();
	if (pid < 0)
		errors("fork");
	if (pid == 0)
	{
		close(fd[1]);
		ft_cp(argv[3], env, fd[0], fd_out);
	}
	ft_wait(pid, fd[0]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;

	if (argc == 5)
	{
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0 || fd_in < 0)
			return (1);
		ft_pipe(argv, env, fd_in, fd_out);
		close(fd_in);
		close(fd_out);
	}
	else
	{
		ft_printf("try: <file1> <cmd1> <cmd2> <file2>\n");
		return (1);
	}
	return (0);
}
