/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:18 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/04 19:46:13 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "ft_glib/ft_glib.h"
# include <libgen.h>
# define MAX_RES_X 2560
# define MAX_RES_Y 1440
# ifdef BONUS
#  define AALVL 50
#  define THREADX 5
#  define THREADY 5
#  include <pthread.h>
# endif

struct s_shape;

int g_error;

enum	e_shapes
{
	SPHERE,
	TRIANGLE,
	PLANE,
	CYLINDER,
	SQUARE
};

typedef union	u_shapes
{
	t_sphere	sphere;
	t_triangle	triangle;
	t_plane		plane;
	t_cylinder	cylinder;
	t_square	square;
}				t_shapes;

typedef struct	s_rot_data
{
	double		r_sin;
	double		r_cos;
	t_v3double	axe;
}				t_rot_data;

typedef struct	s_cam
{
	t_v3double		pos;
	t_v3double		rot;
	int				fov;
	t_rot_data		rot_data;
	t_image			*render;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_alight
{
	double	intensity;
	t_color color;
}				t_alight;

typedef struct	s_light
{
	t_v3double		position;
	double			intensity;
	t_color			color;
	struct s_light	*next;
}				t_light;

typedef union	u_func_types
{
	double	(*distance) (struct s_shape shape, t_v3double point);
	double	(*collision) (struct s_shape shape, t_ray ray);
}				t_func_types;

typedef struct	s_shape
{
	struct s_shape	*next;
	int				type;
	t_color			albedo;
	t_shapes		shape_data;
	t_func_types	calculate_fun;
	t_v3double		(*calculate_normal) (double t, struct s_shape s, t_ray ray);
}				t_shape;

typedef struct	s_sdist
{
	t_shape	shape;
	double	distance;
}				t_sdist;

typedef struct	s_scene
{
	t_vector2	resolution;
	t_alight	ambient_light;
	t_cam		*camera;
	t_shape		*shape_list;
	t_light		*light_list;
	void		*mlx_pointer;
	void		*window_pointer;
}				t_scene;

typedef struct	s_thread_food
{
	t_scene		scene;
	t_image		*image;
	t_vector2	tl;
	t_vector2	br;
}				t_thread_food;

int				ft_atoi(const char *str);
double			ft_atof(const char *str);
int				ft_isspace(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strilen(const char *str);
int				flen(char *str);
int				blend_light(t_sdist surface, t_scene scene, t_ray cam_ray);
int				ft_puts(const char *str, int ret);
int				skip_spaces(char *str);
int				calculate_color(t_ray ray, t_scene scene);
t_color			ft_atoc(const char *str);
double			ft_atof(const char *str);
t_v3double		get_v3f(char **str);
t_vector2		get_res(char *line);
t_alight		get_alight(char *line);
void			add_cam(char *line, t_cam **cam_list);
void			add_sphere(char *line, t_shape **shape_list);
void			add_light(char *line, t_light **light_list);
void			add_plane(char *line, t_shape **shape_list);
void			add_triangle(char *line, t_shape **shape_list);
void			add_cylinder(char *line, t_shape **shape_list);
void			add_square(char *line, t_shape **shape_list);
t_v3double		calculate_sphere_normal(double t, t_shape shape, t_ray ray);
t_v3double		calculate_triangle_normal(double f, t_shape shape, t_ray ray);
t_v3double		calculate_square_normal(double f, t_shape shape, t_ray ray);
t_v3double		calculate_plane_normal(double f, t_shape shape, t_ray ray);
t_v3double		calculate_cylinder_normal(double f, t_shape shape, t_ray ray);
double			point_to_sphere(t_v3double point, t_sphere sphere);
double			check_sphere_collisions(t_shape shape, t_ray line);
double			check_triangle_collisons (t_shape shape, t_ray line);
double			check_square_collision(t_shape shape, t_ray line);
double			check_cylinder_collision(t_shape shape, t_ray line);
double			check_plane_collisons(t_shape shape, t_ray line);
double			plane_intersecton(t_plane plane, t_ray line);
t_light			new_light(t_v3double position, double intensity, t_color color);
t_light			*get_light(char *line);
t_image			*trace(t_scene scene, t_image *image);
double			ft_fminpos(double a, double b);
void			calculate_rotation_data(t_cam *cam);
int				k_hook(int keycode, void *param);
void			next_view(t_scene *scene);
void			yeet(t_scene scene, int ret, char *errorstr);
int				xyeet(void *param);

void			db_print_vector(t_v3double v);
void			db_print_color(t_color c);

#endif
