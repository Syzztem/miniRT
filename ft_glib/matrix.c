/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 14:56:11 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/11 12:19:55 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glib.h"
#include <stdlib.h>

t_matrix	initialize_matrix(void)
{
	float	**mat;
	int		i;

	mat = malloc(sizeof(float*) * 4);
	i = 0;
	while (i < 4)
		mat[i++] = malloc(sizeof(float) * 4);
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
	return (mat);
}

t_v3float	matxvec(t_matrix mat, t_v3float vec)
{
	float a;
	float b;
	float c;
	float w;

	a = vec.x * mat[0][0] + vec.y * mat[1][0] + vec.z * mat[2][0] + mat[3][0];
	b = vec.x * mat[0][1] + vec.y * mat[1][1] + vec.z * mat[2][1] + mat[3][1];
	c = vec.x * mat[0][2] + vec.y * mat[1][2] + vec.z * mat[2][2] + mat[3][2];
	w = vec.x * mat[0][3] + vec.y * mat[1][3] + vec.z * mat[2][3] + mat[3][3];
	return (new_v3f(a / w, b / w, c / w));
}

t_v3float	matxdir(t_matrix mat, t_v3float dir)
{
	t_v3float out;

	out.x = dir.x * mat[0][0] + dir.y * mat[1][0] + dir.z * mat[2][0];
	out.y = dir.x * mat[0][1] + dir.y * mat[1][1] + dir.z * mat[2][1];
	out.z = dir.x * mat[0][2] + dir.y * mat[1][2] + dir.z * mat[2][2];
	return (out);
}
