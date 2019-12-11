/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:18 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/10 14::47 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "ft_glib/ft_glib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

struct s_shape;

enum e_shapes
{
	SPHERE
};

typedef union	u_shapes
{
	t_sphere sphere;
}				t_shapes;

typedef struct	s_cam
{
	t_vector3	pos;
	t_v3float	rot;
	int			fov;
}				t_cam;

typedef struct	s_alight
{
	float	intensity;
	int		color;
}				t_alight;

typedef struct	s_scene
{
	t_vector2	resolution;
	t_alight	light;
	t_cam		camera;
}				t_scene;

typedef struct	s_light
{
	t_v3float	position;
	float		intensity;
	t_color		color;
}				t_light;

typedef union	u_func_types
{
	float	(*distance) (struct s_shape shape, t_v3float point);
	float	(*collision) (struct s_shape shape, t_ray ray);
}				t_func_types;

typedef struct	s_shape
{
	int				type;
	t_color			color;
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


int				ft_atoi(const char *str);
int				ft_isspace(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strilen(const char *str);
int				ft_atoc(const char *str);
float			ft_atof(const char *str);
t_v3float		get_v3f(char **str);
t_vector3		get_v3(char **str);
t_vector2		get_res(char *line);
t_alight		get_light(char *line);
t_cam			mom_get_camera(char *line);
t_v3float		calculate_sphere_normal(float t, t_shape shape, t_ray ray);
float			point_to_sphere(t_v3float point, t_sphere sphere);
float			check_sphere_collisions(t_shape shape, t_ray line);
float			lerp_light(t_light light, t_v3float normal, t_v3float hitpoint);
t_light			new_light(t_v3float position, float intensity, t_color color);

#endif