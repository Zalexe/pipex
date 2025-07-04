/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:05:54 by cmarrued          #+#    #+#             */
/*   Updated: 2025/02/19 18:05:57 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error_exit("Failed to pipe", 1);
	pid = fork();
	if (pid == -1)
		error_exit("Failed to fork", 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (dup(STDIN_FILENO) == -1)
			error_exit("dup error", 1);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc_child(char *limiter, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strnstr(line, limiter, ft_strlen(limiter)) != NULL)
			break ;
		write(fd[1], line, ft_strlen(line));
	}
	free(line);
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];

	if (argc < 6)
		bad_arguments();
	if (pipe(fd) == -1)
		error_exit("Failed to link pipe to fd", 1);
	reader = fork();
	if (reader == 0)
	{
		here_doc_child(limiter, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	pipex_set(int argc, char **argv, char **envp)
{
	int	fileout;
	int	filein;
	int	i;

	if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		fileout = open_file(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		filein = open_file(argv[1], 2);
		fileout = open_file(argv[argc - 1], 1);
		if (filein == -1)
			filein = open("/dev/null", O_RDONLY);
		dup2(filein, STDIN_FILENO);
	}
	if (fileout != -1)
		dup2(fileout, STDOUT_FILENO);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	if (fileout == -1)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		bad_arguments();
		return (1);
	}
	pipex_set(argc, argv, envp);
	execute(argv[argc - 2], envp);
}
