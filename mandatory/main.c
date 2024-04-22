/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/22 15:45:39 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	permissions(char *s, int amode)
{
	if (access(s, F_OK) == 0)
	{
		if (access(s, amode) == 0)
			return (0);
		perror(s);
		return (1);
	}
	else
	{
		perror(s);
		return (1);
	}
}

int	main (int argc, char **argv)
{
	char	*file1;
	char	**cmd1;

	cmd1 = NULL;
	if (argc == 1)
		return (1);
	file1 = argv[1];
	if (permissions(file1, R_OK) == 1)
		return (1);
	if (argc > 2)
	{
		cmd1 = ft_split(argv[2], ' ');
		if (execve(ft_strjoin("/usr/bin/", cmd1[0]), cmd1, NULL) != 0)
		{
			perror(argv[2]);
			return (1);
		}
		ft_printf("something happend \n");
	}
	return (0);
}
