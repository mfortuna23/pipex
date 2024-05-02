/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfortuna <mfortuna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:52:24 by mfortuna          #+#    #+#             */
/*   Updated: 2024/05/02 15:33:45 by mfortuna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "./mylibft/mylibft.h"
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	ft_clean(int argc, int **fd);
int		**ft_pipe_fds(int n_fd);
void	ft_close_files(int **fd);
void	ft_clean_proc(int n_fd, int **fd, int *pid);

#endif