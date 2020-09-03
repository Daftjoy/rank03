/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:35:03 by antmarti          #+#    #+#             */
/*   Updated: 2020/09/03 12:03:21 by antmarti         ###   ########.fr       */
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
		return (ft_error("Error zone format\n"));
	return (0);
}

int		ft_get_shape(int ret, t_shape shape)
{
	if (ret != 6 || (shape.type != 'r' && shape.type != 'R')
	|| shape.width <= 0 || shape.height <= 0)
		return (ft_error("Error shape format\n"));
	return (0);
}

char	*ft_background(t_zone zone)
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

int		ft_isinside(t_shape shape, int i, int j)
{
	if (i >= shape.y && i < shape.y + shape.height &&
			j >= shape.x && j < shape.x + shape.width)
		return (1);
	return (0);
}

char	*ft_fill(t_zone zone, t_shape shape, char *drawing)
{
	int i;
	int j;

	i = 0;
	while (i < zone.height)
	{
		j = 0;
		while (j < zone.width)
		{
			if (ft_isinside(shape, i, j) && (shape.type == 'R'
			|| (shape.type == 'r' && ((i == 0 || j == 0) ||
			(!(ft_isinside(shape, i, j - 1) &&
			ft_isinside(shape, i - 1, j) && ft_isinside(shape, i, j + 1)
			&& ft_isinside(shape, i + 1, j)))))))
				drawing[(i * zone.width) + j] = shape.color;
			j++;
		}
		i++;
	}
	return (drawing);
}

void	ft_printer(t_zone zone, char *drawing)
{
	int i;

	i = 0;
	while (i < zone.height)
	{
		write(1, drawing + (i * zone.width), zone.width);
		write(1, "\n", 1);
		i++;
	}
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
	while ((ret = fscanf(fd, "%c %f %f %f %f %c\n", &shape.type,
	&shape.x, &shape.y, &shape.width, &shape.height, &shape.color)) > 0)
	{
		if (ft_get_shape(ret, shape) == 1)
			return (1);
		if (!(drawing = ft_background(zone)))
			return (ft_error("Malloc error"));
		drawing = ft_fill(zone, shape, drawing);
		ft_printer(zone, drawing);
		write(1, "\n", 1);
		free(drawing);
	}
	return (0);
}
