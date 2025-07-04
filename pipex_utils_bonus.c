/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:18:32 by cmarrued          #+#    #+#             */
/*   Updated: 2025/02/25 13:18:36 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	bad_arguments(void)
{
	ft_putstr_fd("Error: Bad argument", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("or \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_FAILURE);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
	{
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	else if (i == 2)
	{
		file = open(argv, O_RDONLY);
	}
	if (file == -1)
		return (perror("Error opening output file"), -1);
	return (file);
}
