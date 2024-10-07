/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexlib.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-roi <hle-roi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:09:49 by hle-roi           #+#    #+#             */
/*   Updated: 2024/03/19 17:03:28 by hle-roi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEXLIB_H
# define PIPEXLIB_H

# include <unistd.h>
# include <fcntl.h>
# include "ft_printf/includes/ft_printf.h"
# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>

char	*get_path(char *cmd, char **env);
void	free_array(char **array);

#endif