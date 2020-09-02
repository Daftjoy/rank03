/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 10:58:41 by antmarti          #+#    #+#             */
/*   Updated: 2020/09/02 10:58:44 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_zone
{
	int		width;
	int		height;
	char	background;
} 				t_zone;

typedef struct	s_shape
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
	struct s_shape	*next;
}				t_shape;