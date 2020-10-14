/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:20:28 by lothieve          #+#    #+#             */
/*   Updated: 2020/10/14 12:23:22 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLIB_H
# define FT_GLIB_H
# define DEG_TO_RAD 0.01745329251
# define EPSILON 0.0001
# include "get_next_line.h"
# ifdef LINUX
#  include "../minilibx-linux/mlx.h"
# else
#  include <mlx.h>
# endif
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef double **t_matrix;

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
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
}				t_color;

typedef struct	s_v3double
{
	double x;
	double y;
	double z;
}				t_v3double;

typedef struct	s_ray
{
	t_v3double	origin;
	t_v3double	direction;
}				t_ray;

typedef struct	s_plane
{
	t_v3double normal;
	t_v3double p;
}				t_plane;

typedef struct	s_triangle
{
	t_v3double	vertices[3];
	t_v3double	ab;
	t_v3double	ac;
	t_v3double	normal;
}				t_triangle;

typedef struct	s_sphere
{
	t_v3double	center;
	double		radius;
}				t_sphere;

typedef struct	s_cylinder
{
	t_v3double	pos;
	t_v3double	orientation;
	t_v3double	capa;
	t_v3double	capb;
	t_v3double	ca;
	double		caca;
	double		radius;
	double		height;
}				t_cylinder;

typedef struct	s_square
{
	t_v3double	pos;
	t_v3double	orientation;
	double		side;
}				t_square;

typedef struct	s_image
{
	void		*img_ptr;
	t_vector2	res;
	int			*img_data;
	char		bpp;
	int			size_line;
	int			endian;
}				t_image;

typedef struct	s_mesh
{
	t_v3double	*vertices;
	t_v3double	*triangles;
}				t_mesh;

typedef t_image	*(t_filter)(t_image *image);
double			square(double f);
double			v3f_dist_lp(t_ray line, t_v3double point);
int				get_color(t_color color);
int				get_color_i(int r, int g, int b);
int				median_color(int *levels, int size);
double			v3f_magnitude(t_v3double v);
double			v3f_dot(t_v3double u, t_v3double v);
double			v3f_square(t_v3double v);
double			solve_quadra(double a, double b, double c);
double			ft_atof(const char *str);
t_v3double		new_v3f(double x, double y, double z);
t_v3double		to_v3f(t_vector3 v);
t_v3double		v3f_cross(t_v3double u, t_v3double v);
t_v3double		v3f_multiply(t_v3double u, double n);
t_v3double		v3f_divide_x(t_v3double u, double n);
t_v3double		v3f_normalize(t_v3double v);
t_v3double		v3f_sub(t_v3double u, t_v3double v);
t_v3double		v3f_add(t_v3double u, t_v3double v);
t_v3double		ray_point_at(t_ray ray, double t);
t_v3double		matxvec(t_matrix mat, t_v3double vec);
t_v3double		matxdir(t_matrix mat, t_v3double dir);
t_sphere		new_sphere(t_v3double center, double radius);
t_ray			new_ray(t_v3double origin, t_v3double direction);
t_ray			ray_from_points(t_v3double a, t_v3double b);
t_color			new_color(unsigned char r, unsigned char g, unsigned char b);
t_color			col_multiply(t_color color, double value);
t_color			col_add(t_color a, t_color b);
t_color			col_multiply_c(t_color a, t_color b);
t_color			col_merge(t_color a, t_color b);
t_color			new_color_i(int color);
t_matrix		initialize_matrix();
t_plane			new_plane(t_v3double normal, t_v3double p);
t_v3double		v3f_rotate(t_v3double in, t_v3double axe, double s, double c);
t_image			*generate_image(t_vector2 res, void *mlx_ptr);
t_image			*filter_bw(t_image *image);
t_image			*filter_sepia(t_image *image);
t_image			*filter_inv(t_image *image);
size_t			ft_strlen(const char *str);
unsigned char	sat_add(unsigned char a, unsigned char b);
int				create_bitmap(t_image image, char *filename);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			image_pixel_put(t_image *image, int x, int y, int color);
float			randfloat();

#endif
