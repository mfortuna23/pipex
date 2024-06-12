/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:10:02 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/07 10:19:05 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_pipe(char *cmd, char **env, int fd_in)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		exit(2); // create function that deals with this
	pid = fork();
	if (pid < 0)
		exit(3); // create a function that deals with this
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (fd_in == STDIN_FILENO)
			exit(1);
		else
			ft_cp(cmd, env);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;
	int	i;

	i = 1;
	if (argc > 5)
	{
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0 || fd_in < 0)
			return (1);
		while (++i < (argc - 2))
			ft_pipe(argv[i], env, fd_in);
		ft_cp(argv[i], env);
		close(fd_in);
		close(fd_out);
		return (0);
	}
	ft_printf("not enogh arguments\n");
	return (1);
}
