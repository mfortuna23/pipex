/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/30 14:51:04 by mfortuna         ###   ########.fr       */
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
static int forking(int argc, char **argv, char **env, int fd)
{
	
}

static int child_process(char **cmd, int fd_read, int fd_write, int id)
{
	char	*cmd_path;
	int		char_read;
	char	buffer[1024];

	char_read = 1;
	cmd_path = NULL;
	if (cmd[0] == 0)
	{
		while (char_read != 0)
		{
			ft_putstr_fd(buffer, fd_write);
			char_read = read(fd_read, buffer, 1024);
		}
		close(fd_read);
		close(fd_write);
		exit(0);
	}
	cmd_path = find_path(cmd[0]);
	if (cmd_path == NULL)
		exit(1);
	waitpid(0, NULL, 0);
	if (execve(cmd_path, cmd, NULL) == -1)
		return (ft_printf("execve didn't work in process: %i O__O\n", id));
}

int	main(int argc, char **argv, char **env)
{
	int	fd_src;
	int	fd_dst;
	int	check;

	check = 1;
	if (argc == 5)
	{
		fd_src = file_open(argv[1], 0);
		fd_dst = file_open(argv[argc - 1], 26);
		dup2(fd_src, STDOUT_FILENO);
		dup2(fd_dst, STDIN_FILENO);
		close(fd_src);
		close(fd_dst);
		forking(argc, argv, env, STDOUT_FILENO);
	}
	ft_printf("4 arguments please :)\n");
	return (1);
}

