/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:18:49 by hbulut            #+#    #+#             */
/*   Updated: 2025/02/20 09:56:55 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	executive_process(char *cmd, char **env)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	if (!command[0])
		exit(0);
	if (cmd[0] == '/')
	{
		if (execve(cmd, command, env) == -1)
		{
			perror("Error");
			free_trash(command);
			exit(0);
		}
	}
	path = split_path(env, cmd);
	if (execve(path, command, env) == -1)
	{
		ft_putstr_fd("Error: command not found\n", 2);
		free_trash(command);
		exit(0);
	}
}

void	child(char **argv, int *pipedes, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd, 0);
	dup2(pipedes[1], 1);
	close(pipedes[0]);
	executive_process(argv[2], env);
}

void	parent(char **argv, int *pipedes, char **env)
{
	int		fd;

	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(fd, 1);
	dup2(pipedes[0], 0);
	close(pipedes[1]);
	executive_process(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		pipedes[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid arguman!./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	if (pipe(pipedes) == -1)
	{
		perror("Error");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(-1);
	}
	if (pid == 0)
		child(argv, pipedes, env);
	waitpid(pid, NULL, 0);
	parent(argv, pipedes, env);
	return (0);
}
