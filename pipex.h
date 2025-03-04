/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbulut <hbulut@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:18:52 by hbulut            #+#    #+#             */
/*   Updated: 2025/02/20 09:17:48 by hbulut           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

char	*get_command_path(char **env);
void	free_trash(char **tab);
char	*split_path(char **env, char *command);
void	executive_process(char *cmd, char **env);
void	child(char **argv, int *pipedes, char **env);
void	parent(char **argv, int *pipedes, char **env);
int		main(int argc, char **argv, char **env);

#endif