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

void	error_exit(const char *message, int error)
{
	perror(message);
	exit(error);
}

void	clean_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (clean_cmd(paths), path);
		free(path);
		i++;
	}
	clean_cmd(paths);
	return (0);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (ft_strncmp(argv, "", 1) == 0)
		error_exit("Command is empty", 1);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_exit("Memory allocation failed for command arguments", 1);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		clean_cmd(cmd);
		error_exit("Error parsing commands", 127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		clean_cmd(cmd);
		free(path);
		error_exit("Error executing command", 127);
	}
	clean_cmd(cmd);
	free(path);
}
