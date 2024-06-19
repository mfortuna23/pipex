/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:25:11 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/19 13:17:29 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	errors(char *s)
{
	perror(s);
	exit(1);
}

int	ft_wait(pid_t pid1, pid_t pid2, int fd1, int fd2)
{
	int	status;

	waitpid(pid1, 0, WNOHANG);
	close(fd2);
	waitpid(pid2, &status, 0);
	close(fd1);
	return (WEXITSTATUS(status));
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
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_freearr(paths);
	paths = NULL;
	full_path = NULL;
	return (0);
}
char	**ft_fullcmd(char *cmd)
{
	char	**arr;
	int		i;
	
	arr = NULL;
	if (ft_strrchr(cmd, '\'') == NULL && ft_strrchr(cmd, '\"') == NULL)
		return(ft_split(cmd, ' '));
	arr = ft_calloc(3, sizeof(char *));
	if (!arr)
		return(arr);
	while (cmd[i] == ' ')
		i++;
	while (cmd[i] != ' ')
		i++;
	arr[0] = ft_substr(cmd, 0, i);
	i += 2;
	arr[1] = ft_substr(cmd, i, (ft_strlen(cmd + i)) - 1);
	return (arr);
}

void	ft_cp(char *cmd, char **env, int fd_in, int fd_out)
{
	char	**full_cmd;
	char	*path;

	full_cmd = ft_fullcmd(cmd);
	path = find_path(full_cmd[0], env);
	if (path == NULL)
	{
		close(fd_in);
		close(fd_out);
		ft_putstr_fd(full_cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		ft_freearr(full_cmd);
		exit(127);
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


