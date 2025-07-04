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

void	child_exec(char **argv, char **envp, int *pipefd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error_exit("Error open filein child", 1);
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(pipefd[0]);
	close(filein);
	execute(argv[2], envp);
}

void	parent_exec(char **argv, char **envp, int *pipefd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		error_exit("Error open fileout parent", 1);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(pipefd[1]);
	close(fileout);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	parent;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	else
	{
		if (ft_strncmp(argv[2], "", 1) == 0 || ft_strncmp(argv[3], "", 1) == 0)
			error_exit("One command is empty", 1);
		if (pipe(pipefd) == -1)
			error_exit("pipe failed", 1);
		parent = fork();
		if (parent == -1)
			error_exit("fork failed", 1);
		if (parent == 0)
			child_exec(argv, envp, pipefd);
		waitpid(parent, NULL, 0);
		parent_exec(argv, envp, pipefd);
	}
	return (0);
}
