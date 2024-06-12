/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:25:11 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/12 12:08:00 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errors(char *s)
{
	perror(s);
	exit(1);
}

void	ft_wait(pid_t pid, int fd)
{
	int	status;
	int	i;

	i = 0;
	while (i < 10000)
	{
		waitpid(pid, &status, WNOHANG);
		if (WIFEXITED(status) == 1)
		{
			close(fd);
			return ;
		}
		else
			i++;
	}
	close(fd);
}

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
		exit(1);
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
	errors("execve");
}


