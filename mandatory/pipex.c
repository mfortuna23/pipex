/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.pt>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/28 14:14:38 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errors(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
	exit(3);
}

int	file_opener(char *file, int write)
{
	if (write == 0)
	{
		if (access(file, X_OK) < 0)
			errors("1st file doesn't exist\n");
		if (access(file, R_OK) < 0)
			errors("Can't read 1st file\n");
		return (open(file, O_RDONLY));
	}
	return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

char	*find_path(char *cmd)
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
			ft_putstr_fd("command \"", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd("\" not found", STDERR_FILENO);
			free(full_path);
			ft_freearr(paths, 3);
			return (NULL);
		}
		free(full_path);
		full_path = ft_strjoin(paths[i], cmd);
		i++;
	}
	ft_freearr(paths, 3);
	return (full_path);
}

int	ft_cp(char *cmd, char **env, int fd_in, int fd_out)
{
	char	**full_cmd;
	char	*path;

	full_cmd = ft_split(cmd, ' ');
	path = find_path(full_cmd[0]);
	if (path == NULL)
	{
		close(fd_in);
		close(fd_out);
		ft_freearr(full_cmd, ft_countmywords(cmd, ' '));
		return (42);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
		errors("dup2 didnt work\n");
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		errors("dup2 didnt work\n");
	close(fd_in);
	close(fd_out);
	execve(path, full_cmd, env);
	free(path);
	path = NULL;
	ft_freearr(full_cmd, ft_countmywords(cmd, ' '));
	ft_putstr_fd("execve didn't work\n", STDERR_FILENO);
	return (42);
}

void	ft_pipe(char **argv, char **env, int fd_in, int fd_out)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) < 0)
		errors("couldnt pipe fd\n");
	pid1 = fork();
	if (pid1 < 0)
		errors("couldn't fork the process\n");
	if (pid1 == 0)
	{
		close(fd[0]);
		if(ft_cp(argv[2], env, fd_in, fd[1]) == 42)
			exit(42);
	}
	pid2 = fork();
	if (pid2 < 0)
		errors("couldn't fork the process\n");
	if (pid2 == 0)
	{
		close(fd[1]);
		if(ft_cp(argv[3], env, fd[0], fd_out) == 42)
			exit(42);
	}
	waitpid(pid1, NULL, 0);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
	close(fd[0]);
}

int	main(int argc, char **argv, char **env)
{
	int	fd_in;
	int	fd_out;

	if (argc == 5)
	{
		fd_in = file_opener(argv[1], 0);
		fd_out = file_opener(argv[argc - 1], 1);
		ft_pipe(argv, env, fd_in, fd_out);
		close(fd_in);
		close(fd_out);
	}
	else
		ft_printf("try: <file1> <cmd1> <cmd2> <file2>\n");
	return (0);
}
