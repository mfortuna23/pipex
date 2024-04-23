/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:01 by mfortuna          #+#    #+#             */
/*   Updated: 2024/04/23 18:15:32 by mfortuna         ###   ########.fr       */
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
static int	parent_proc(char **argv);

static int	child_proc(char **argv);

static int	ft_pipe(char *file1, char **cmd1, char **cmd2, char *file2)
{
	char	*cmd1_path;
	char	*cmd2_path;

	cmd1_path = ft_strjoin("/bin/", cmd1[0]);
	cmd2_path = ft_strjoin("/bin/", cmd2[0]);
}

int	main(int argc, char **argv)
{
	int	cmd;

	cmd = 0;
	if (argc == 5)
	{
		if (permissions(argv[1], R_OK) == 1)
			return (1);
		cmd = ft_pipe(argv[1], ft_split(argv[2], " "), ft_split(argv[3], " ") \
		, argv[4]);
	}
	if (argc < 4)
		ft_printf("I can't work with this. NOT ENOUGH ARGUMENTS!!");
	if (argc > 5)
		ft_printf("I can only work with 'file1 cmd1 cmd2 file2'");
	return (1);
}
