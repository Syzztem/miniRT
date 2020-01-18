/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:18 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/18 16:15:08 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "ft_glib/ft_glib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# define VIEW_DISTANCE 10000000000
# define EPSILON 0.00001f

struct s_shape;

enum e_shapes
{
	SPHERE,
	TRIANGLE,
	PLANE
};

typedef union	u_shapes
{
	t_sphere	sphere;
	t_triangle	triangle;
	t_plane		plane;
}				t_shapes;

typedef struct	s_rot_data
{
	float		r_sin;
	float		r_cos;
	t_v3float	axe;
}				t_rot_data;

typedef struct	s_cam
{
	t_v3float		pos;
	t_v3float		rot;
	int				fov;
	t_rot_data		rot_data;
	t_image			render;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_alight
{
	float	intensity;
	t_color color;
}				t_alight;

typedef struct	s_light
{
	t_v3float		position;
	float			intensity;
	t_color			color;
	struct s_light	*next;
}				t_light;

typedef union	u_func_types
{
	float	(*distance) (struct s_shape shape, t_v3float point);
	float	(*collision) (struct s_shape shape, t_ray ray);
}				t_func_types;

typedef struct	s_shape
{
	int				type;
	t_color			albedo;
	t_shapes		shape_data;
	struct s_shape	*next;
	t_func_types	calculate_fun;
	t_v3float		(*calculate_normal) (float t, struct s_shape shape, t_ray ray);
}				t_shape;

typedef struct	s_sdist
{
	t_shape	shape;
	float	distance;
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

int				ft_atoi(const char *str);
float			ft_atof(const char *str);
int				ft_isspace(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strilen(const char *str);
t_color			ft_atoc(const char *str);
float			ft_atof(const char *str);
t_v3float		get_v3f(char **str);
t_vector3		get_v3(char **str);
t_vector2		get_res(char *line);
t_alight		get_alight(char *line);
void			add_cam(char *line, t_cam **cam_list);
void			add_sphere(char *line, t_shape **shape_list);
void			add_light(char *line, t_light **light_list);
void			add_plane(char *line, t_shape **shape_list);
t_v3float		calculate_sphere_normal(float t, t_shape shape, t_ray ray);
float			point_to_sphere(t_v3float point, t_sphere sphere);
float			check_sphere_collisions(t_shape shape, t_ray line);
int				lerp_light(t_light *light, t_ray normal_ray, t_color albedo, t_scene scene);
t_light			new_light(t_v3float position, float intensity, t_color color);
float			check_plane_collisons (t_shape shape, t_ray line);
t_v3float		calculate_plane_normal(float f, t_shape shape, t_ray ray);
void			calculate_rotation_data(t_cam *cam);
int				k_hook(int keycode, void *param);
void			next_view(t_scene *scene);

void db_print_vector(t_v3float v);
void db_print_color(t_color c);

#endif