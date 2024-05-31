/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/29 17:12:50 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errors(char *s)
{
	perror(s);
	exit(1);
}
/* char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
} */

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*half_path;
	char	*full_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		half_path = ft_strjoin(paths[i], "/" );
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_freearr(paths);
	return (0);
}

void	ft_cp(char *cmd, char **env, int fd_in, int fd_out)
{
	char	**full_cmd;
	char	*path;

	full_cmd = ft_split(cmd, ' ');
	path = find_path(full_cmd[0], env);
	if (path == NULL)
	{
		close(fd_in);
		close(fd_out);
		ft_freearr(full_cmd);
		exit(42);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
		errors("dup2");
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		errors("dup2");
	close(fd_in);
	close(fd_out);
	execve(path, full_cmd, env);
	free(path);
	path = NULL;
	ft_freearr(full_cmd);
	ft_putstr_fd("execve didn't work\n", STDERR_FILENO);
	exit(1);
}

void	ft_pipe(char **argv, char **env, int fd_in, int fd_out)
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
	waitpid(pid, NULL, 0);
	close(fd[1]);
	pid = fork();
	if (pid < 0)
		errors("fork");
	if (pid == 0)
	{
		close(fd[1]);
		ft_cp(argv[3], env, fd[0], fd_out);
	}
	waitpid(pid, NULL, 0);
	close(fd[0]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;

	if (argc == 5)
	{
		fd_in = open(argv[1], O_RDONLY);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_pipe(argv, env, fd_in, fd_out);
		close(fd_in);
		close(fd_out);
	}
	else
		ft_printf("try: <file1> <cmd1> <cmd2> <file2>\n");
	return (0);
}
