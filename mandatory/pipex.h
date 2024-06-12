/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/06/12 11:15:11 by mfortuna         ###   ########.fr       */
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
void	ft_wait(pid_t pid, int fd);
char	*find_path(char *cmd, char **env);
void	ft_cp(char *cmd, char **env, int fd_in, int fd_out);
#endif
