/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/19 13:17:13 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./mylibft/mylibft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>

void	errors(char *s);
int	ft_wait(pid_t pid1, pid_t pid2, int fd1, int fd2);
char	*find_path(char *cmd, char **env);
void	ft_cp(char *cmd, char **env, int fd_in, int fd_out);
#endif
