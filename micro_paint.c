/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:35:03 by antmarti          #+#    #+#             */
/*   Updated: 2020/09/02 12:34:13 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "micro_paint.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_error(char *err)
{
	write(1, err, ft_strlen(err));
	return (1);
}

int		ft_get_zone(int ret, t_zone zone)
{
	if (ret != 3 || zone.width < 0 || zone.width > 300 ||
	zone.height < 0 || zone.height > 300)
		return (ft_error("Error\n"));
	return (0);
}

int		ft_get_shape(int ret, t_shape shape)
{
	if (ret != 6 || (shape.type != 'r' && shape.type != 'R')
	|| shape.width <= 0.0 || shape.height <= 0.0)
		return (ft_error("Error\n"));
	return (0);
}

char	*ft_background(t_zone zone, t_shape shape)
{
	char	*drawing;
	int		i;

	i = 0;
	if (!(drawing =
	(char*)malloc(sizeof(*drawing) * (zone.width * zone.height))))
		return (0);
	while (i < zone.width * zone.height)
		drawing[i++] = zone.background;
	return (drawing);
}

int		main(int argc, char **argv)
{
	FILE	*fd;
	int		ret;
	t_zone	zone;
	t_shape	shape;
	char	*drawing;

	if (argc != 2)
		return (ft_error("Error: argument\n"));
	if (!(fd = fopen(argv[1], "r")))
		return (ft_error("Error: Operation file corrupted\n"));
	ret = fscanf(fd, "%d %d %c\n", &zone.width, &zone.height, &zone.background);
	if (ft_get_zone(ret, zone) == 1)
		return (1);
	ret = fscanf(fd, "%c %f %f %f %f %c", &shape.type, &shape.x, &shape.y,
	&shape.width, &shape.height, &shape.color);
	if (ft_get_shape(ret, shape) == 1)
		return (1);
	drawing = ft_background(zone, shape);
	return (0);
}
