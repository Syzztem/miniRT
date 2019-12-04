/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:20:28 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/04 14:25:21 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLIB_H
# define FT_GLIB_H
# include <mlx.h>
# include <math.h>

typedef struct	s_vector3
{
	int x;
	int y;
	int z;
}				t_vector3;

typedef struct	s_vector2
{
	int x;
	int y;
}				t_vector2;

typedef struct	s_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}				t_color;

typedef struct	s_v3float
{
	float x;
	float y;
	float z;
}				t_v3float;

typedef struct	s_ray
{
	t_v3float	origin;
	t_v3float	direction;
}				t_ray;

typedef struct	s_sphere
{
	t_v3float	center;
	float		radius;
	int			color;
}				t_sphere;

float			square(float f);
float			v3f_dist_lp(t_ray line, t_v3float point);
int				get_color(t_color color);
int				get_color_i(int r, int g, int b);
float			v3f_magnitude(t_v3float v);
float			v3f_dot(t_v3float u, t_v3float v);
t_v3float		new_v3f(float x, float y, float z);
t_v3float		to_v3f(t_vector3 v);
t_v3float		v3f_multiply_v(t_v3float u, t_v3float v);
t_v3float		v3f_multiply_x(t_v3float u, float n);
t_v3float		v3f_divide_x(t_v3float u, float n);
t_v3float 		v3f_normalize(t_v3float v);
t_v3float		v3f_substract_v(t_v3float u, t_v3float v);
t_v3float		v3f_add(t_v3float u, t_v3float v);
t_v3float		ray_point_at(t_ray ray, float t);
t_sphere		new_sphere(t_v3float center, float radius);
t_ray			new_ray(t_v3float origin, t_v3float direction);
t_color			new_color(unsigned char r, unsigned char g, unsigned char b);

#endif