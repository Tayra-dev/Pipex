/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:40:51 by hle-roi           #+#    #+#             */
/*   Updated: 2024/03/21 10:37:05 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipexlib.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*str;
	char	**paths;
	char	*exec;

	i = 0;
	str = env[find_path(env)];
	str = &str[5];
	paths = ft_split(str, ':');
	while (paths[i])
	{
		str = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(str, cmd);
		free(str);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_array(paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	free_array(paths);
	return (cmd);
}
