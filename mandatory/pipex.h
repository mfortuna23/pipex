/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/08 19:01:58 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./mylibft/mylibft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	ft_clean(int argc, int **fds);
int		**ft_pipe_fds(int n_fd);
void	ft_close_files(int **fd, int n_fds);
void	ft_clean_proc(int n_fd, int **fd, int *pid);

#endif