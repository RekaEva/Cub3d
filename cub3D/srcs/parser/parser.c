/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:19:53 by lbrianna          #+#    #+#             */
/*   Updated: 2022/10/19 15:08:34 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
{
	if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4))
		return (1);
	return (0);
}

char	*read_map(int fd)
{
	char	*str;
	char	*res;
	char	buffer[BUFFER_SIZE + 1];
	int		flag;

	str = ft_strdup("");
	flag = (int)read(fd, buffer, BUFFER_SIZE);
	if (flag == '\0')
		return_error("The file is empty\n", 5);
	while (flag > 0 && *buffer != '\0')
	{
		buffer[flag] = '\0';
		res = ft_strjoin(str, buffer);
		if (res == NULL)
			return_error("Error while allocating memory\n", 5);
		free(str);
		str = res;
		flag = (int)read(fd, buffer, BUFFER_SIZE);
	}
	if (flag < 0)
		return_error("Error while reading file\n", 6);
	return (res);
}

void	parser(char **argv, t_info *data)
{
	char	*str;
	int		fd;

	if (check_extension(argv[1]) == 1)
		return_error("Wrong extension of the file\n", 2);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return_error("Could not open the file\n", 3);
	str = read_map(fd);
	if (close(fd) == -1)
		return_error("Could not close file\n", 4);
	make_data(data, str);
	free(str);
}
