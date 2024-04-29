/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/29 18:28:38 by mfortuna         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	int	fd_src;
	int	fd_dst;

	if (argc == 5)
	{
		fd_src = file_open(argv[1], 0);
		fd_dst = file_open(argv[argc - 1], 26);
	}
	return (1);
}

