/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/12 12:18:47 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	coutarr(char *s)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == 32)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			i++;
			while (s[i] != 34 || s[i] != 39)
				i++;
		}
		while (s[i] != 32)
			i++;
			count ++;
	}
}

char **ft_newsplit (char *s)
{
	char	**arr;
	int		i;
	int		j;

	arr = NULL;
	i = 0;
	arr = ft_calloc(countarr(s), sizeof(char *));
	if (!arr)
		return(arr);
	while (s[i] == ' ')
		i++;
	j = i;
	while ((s[i]) && s[i] != ' ')
		i++;
	arr[0] = ft_substr(s, j, (i - j));
	while (s[i] == 32 | s[i] == 34 | s[i] == 39)
		i++;
	j = i;
	while (s[i] && (s[i] != 34 && s[i] != 39))
		i++;
	arr[1] = ft_substr(s, j, (i - j));
	return (arr);
}

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
