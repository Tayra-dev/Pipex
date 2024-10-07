/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:22:45 by hle-roi           #+#    #+#             */
/*   Updated: 2024/03/21 10:45:31 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipexlib.h"

void	try_cmd(char *cmd, char **env)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	if (cmd[0] == 0)
	{
		ft_putstr_fd("pipex: permission denied: \n", 2);
		exit(EXIT_FAILURE);
	}
	if (env[0] != NULL)
		path = get_path(cmd_split[0], env);
	if (execve(path, cmd_split, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putchar_fd('\n', 2);
		free_array(cmd_split);
		exit(EXIT_FAILURE);
	}
}

void	first_child(char **argv, int *end, char **env)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	try_cmd(argv[2], env);
}

void	second_child(char **argv, int *end, char **env)
{
	int	fd;

	fd = open (argv[4], O_TRUNC | O_RDWR | O_CREAT, 00644);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	try_cmd(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;

	if (argc != 5)
		return (127);
	if (pipe(end) < 0)
		return (127);
	child1 = fork();
	if (child1 < 0)
		return (127);
	if (!child1)
		first_child(argv, end, env);
	child2 = fork();
	if (child2 < 0)
		return (127);
	if (!child2)
		second_child(argv, end, env);
	return (0);
}
