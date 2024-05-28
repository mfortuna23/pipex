/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:25:11 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/22 18:45:43 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cleanfds(int **fds, int cp_id)
{
	int	i;

	i = 0;
	while (i <= cp_id)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
	close(fds[i][0]);
	close(fds[i][1]);
	free(fds[i]);
	while (--i >= 0)
		free(fds[i]);
	free(fds);
}
static void	ft_cp(char *cmd, char **env)
{
	char	**full_cmd;
	char	*cmd_path;

	full_cmd = ft_split(cmd, ' ');
	cmd_path = find_path(full_cmd[0], env);
	execve(cmd_path, full_cmd, env);
	ft_putstr_fd("something went wrong with execve\n", STDERR_FILENO);
	ft_freearr(full_cmd, ft_countmywords(cmd, ' '));
	free(cmd_path);
	exit(2);
}

/* static void	ft_parent(int **fds, pid_t *cp_id, char *src, char *dst)
{
	char	buffer[1024];
	int		fd_src;
	int		fd_dst;
	int		w;

	fd_src = file_open(src, 0);
	w = -1;
	dup2(fds[0][1], STDOUT_FILENO);
	while ((read(fd_src, buffer, 1024)) > 0)
		ft_putstr_fd(buffer, STDOUT_FILENO);
	while (cp_id[++w])
		waitpid(cp_id[w], NULL, 0);
	fd_dst = file_open(dst, 1);
	dup2(fds[w - 1][0], STDIN_FILENO);
	ft_cleanfds(fds, 3);
	while ((read(STDIN_FILENO, buffer, 1024)) > 0)
		ft_putstr_fd(buffer, fd_dst);
	free(cp_id);
	close(fd_src);
	close(fd_dst);
} */

void	ft_forking(char *cmd, char **env, int file1)
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
		if (file1 == STDIN_FILENO)
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
	int	file1;
	int	file2;
	int	i;

	i = 1;
	if (argc == 5)
	{
		file1 = file_open(argv[1], 0);
		file2 = file_open(argv[argc - 1], 42);
		dup2(file1, STDIN_FILENO);
		dup2(file2, STDOUT_FILENO);
		close(file1);
		close(file2);
		while (++i < (argc - 2))
			ft_forking(argv[i], env, 1);
		ft_cp(argv[i], env);
	}
	else
		ft_printf("invalid number of arguments\n");
	return (0);
}


