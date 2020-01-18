/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:20:28 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/13 12:30:39 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLIB_H
# define FT_GLIB_H
# define DEG_TO_RAD 0.01745329251
# include <mlx.h>
# include <math.h>
# include <stdlib.h>

typedef float **t_matrix;

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

typedef struct	s_plane
{
	t_v3float normal;
	t_v3float p;
}				t_plane;

typedef struct	s_triangle
{
	t_v3float	points[3];
	t_plane		plane;
}				t_triangle;

typedef struct	s_sphere
{
	t_v3float	center;
	float		radius;
}				t_sphere;

typedef struct	s_image
{
	void		*img_ptr;
	t_vector2	res;
	int			*img_data;
	char		bpp;
	int			size_line;
	int			endian;
}				t_image;

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
t_v3float		v3f_normalize(t_v3float v);
t_v3float		v3f_substract_v(t_v3float u, t_v3float v);
t_v3float		v3f_add(t_v3float u, t_v3float v);
t_v3float		ray_point_at(t_ray ray, float t);
t_v3float		matxvec(t_matrix mat, t_v3float vec);
t_v3float		matxdir(t_matrix mat, t_v3float dir);
t_sphere		new_sphere(t_v3float center, float radius);
t_ray			new_ray(t_v3float origin, t_v3float direction);
t_ray			ray_from_points(t_v3float a, t_v3float b);
t_color			new_color(unsigned char r, unsigned char g, unsigned char b);
t_color			col_multiply(t_color color, float value);
t_color			col_add(t_color a, t_color b);
t_color			col_multiply_c(t_color a, t_color b);
t_matrix		initialize_matrix();
t_plane			new_plane(t_v3float normal, t_v3float p);
t_v3float		v3f_rotate(t_v3float in, t_v3float axe, float a_sin, float a_cos);
unsigned char	sat_add(unsigned char a, unsigned char b);
int				create_bitmap(t_image image, char *filename);
void			*ft_memcpy(void *dst, const void *src, size_t n);
float			ft_fminpos(float a, float b);

#endif
