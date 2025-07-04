/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:07:55 by cmarrued          #+#    #+#             */
/*   Updated: 2025/02/19 18:07:56 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "Libft/libft.h"

void		parent_exec(char **argv, char **envp, int *pipefd);
void		child_exec(char **argv, char **envp, int *pipefd);
void		error_exit(const char *message, int error);
void		execute(char *argv, char **envp);
void		clean_cmd(char **cmd);
char		*get_path(char	*cmd, char **envp);
// bonus
void		pipex_set(int argc, char **argv, char **envp);
void		bad_arguments(void);
void		here_doc(char *limiter, int argc);
void		here_doc_child(char *limiter, int *fd);
void		child_process_bonus(char *argv, char **envp);
int			open_file(char *argv, int i);
#endif
