/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:18:55 by hbulut            #+#    #+#             */
/*   Updated: 2025/02/20 09:17:57 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char **env)
{
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

void	free_trash(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*split_path(char **env, char *command)
{
	int		i;
	char	*end;
	char	*p_way;
	char	**path;
	char	**cmd;

	i = -1;
	path = ft_split(get_command_path(env), ':');
	cmd = ft_split(command, ' ');
	while (path[++i])
	{
		p_way = ft_strjoin(path[i], "/");
		end = ft_strjoin(p_way, cmd[0]);
		free(p_way);
		if (access(end, F_OK | X_OK) == 0)
		{
			free_trash(cmd);
			return (end);
		}
		free(end);
	}
	free_trash(path);
	free_trash(cmd);
	return (command);
}
