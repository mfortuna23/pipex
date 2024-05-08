/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/08 18:58:39 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	file_open(char *file, int x)
{
	if (x == 0)
	{
		if (access(file, X_OK) != 0)
		{
			perror(file);
			exit(1);
		}
		if (access(file, R_OK) != 0)
		{
			perror(file);
			exit(1);
		}
		return (open(file, O_WRONLY));
	}
	return (open(file, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH));
}

static char	*find_path(char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 1;
	full_path = NULL;
	paths = ft_split("/bin/ /usr/bin/ /usr/local/bin/", ' ');
	full_path = ft_strjoin(paths[0], cmd);
	while (access(full_path, X_OK) != 0)
	{
		if (i == 3)
		{
			ft_printf("command \"%s\" not found", cmd);
			free(full_path);
			ft_freearr(paths, 3);
			return (NULL);
		}
		full_path = ft_strjoin(paths[i], cmd);
		i++;
	}
	ft_freearr(paths, 3);
	return (full_path);
}

static void	child_process(char **cmd, int fd_read, int fd_write, char **env)
{
	char	*cmd_path;

	cmd_path = NULL;
	dup2(fd_read, STDOUT_FILENO);
	dup2(fd_write, STDIN_FILENO);
	close(fd_read);
	close(fd_write);
	if (cmd[0] == 0)
		cmd[0] = "cat";
	cmd_path = find_path(cmd[0]);
	if (cmd_path == NULL)
		exit(1);
	// ft_printf("%s\n", cmd_path);
	execve(cmd_path, cmd, env);
	free(cmd_path);
	exit(ft_printf("execve didn't work O__O\n"));
}

static void	forking(int argc, char **argv, char **env)
{
	int		**fd;
	int		i;
	int		*pid;
	char	**cmd;

	i = 0;
	cmd = NULL;
	fd = ft_pipe_fds(argc - 2);
	pid = ft_calloc(argc - 2, sizeof(int));
	while (i < (argc - 2))
	{
		pid[i] = fork();
		if (pid[i] == -1)
			ft_clean_proc((argc - 3), fd, pid);
		cmd = ft_split(argv[i + 2], ' ');
		if (pid[i] == 0)
			child_process(cmd, fd[i][0], fd[i + 1][1], env);
		ft_freearr(cmd, ft_countmywords(argv[i + 2], ' '));
		waitpid(pid[i], NULL, 0);
		i++;
	}
	ft_clean_proc(i, fd, pid);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_src;
	int	fd_dst;

	if (argc == 5)
	{
		fd_src = file_open(argv[1], 0);
		fd_dst = file_open(argv[argc - 1], 26);
		dup2(fd_src, STDOUT_FILENO);
		dup2(fd_dst, STDIN_FILENO);
		close(fd_src);
		close(fd_dst);
		forking(argc, argv, env);
	}
	ft_printf("4 arguments please :)\n");
	return (1);
}

