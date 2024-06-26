/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/26 14:56:29 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_pipe(char **argv, char **env, int fd_in, int fd_out)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) < 0)
		errors("pipe");
	pid1 = fork();
	if (pid1 < 0)
		errors("fork");
	if (pid1 == 0)
	{
		close(fd[0]);
		ft_cp(argv[2], env, fd_in, fd[1]);
	}
	pid2 = fork();
	if (pid2 < 0)
		errors("fork");
	if (pid2 == 0)
	{
		close(fd[1]);
		ft_cp(argv[3], env, fd[0], fd_out);
	}
	return (ft_wait(pid1, pid2, fd[0], fd[1]));
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;
	int	exit_code;

	if (argc == 5)
	{
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_in < 0 || fd_out < 0)
		{
			if (fd_in < 0)
				perror("file1");
			if (fd_out < 0)
				perror("file2");
			return (1);
		}
		exit_code = ft_pipe(argv, env, fd_in, fd_out);
		close(fd_in);
		close(fd_out);
		return (exit_code);
	}
	ft_printf("try: <file1> <cmd1> <cmd2> <file2>\n");
	return (1);
}
