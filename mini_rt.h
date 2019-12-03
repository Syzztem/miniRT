/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:18 by lothieve          #+#    #+#             */
/*   Updated: 2019/12/02 15:17:57 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include "ft_glib/ft_glib.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

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

typedef struct	s_sphere
{
	t_v3float	center;
	int			radius;
	int			color;
}				t_sphere;

typedef struct	s_shape
{
	t_vector3	position;
}				t_shape;

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
float			check_sphere_collisions(t_line line, t_sphere sphere);

#endif