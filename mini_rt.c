/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2019/11/23 17:43:25 by lothieve         ###   ########.fr       */
/*                            :w                                                */
/* ************************************************************************** */

#include "mini_rt.h"
#include "get_next_line.h"

void
	db_print_scene(t_scene s)
{
	printf("Scene:\nResolution : %d %d\nAmbient light : Intensity: %.3f, Color: %x\nCamera: position: %d,%d,%d rotation: %.3f,%.3f,%.3f angle: %d",
	s.resolution.x, s.resolution.y, s.light.intensity, s.light.color, s.camera.pos.x, s.camera.pos.y, s.camera.pos.z, s.camera.rot.x, s.camera.rot.y, s.camera.rot.z, s.camera.fov);
}

t_shape *complete_shape(t_shape *shape)
{
	if (shape->type == SPHERE)
	{
		shape->calculate_fun.collision = check_sphere_collisions;
		shape->calculate_normal = calculate_sphere_normal;
	}
	return (shape);
}

t_shape *new_shape(int type, t_color color, t_shapes shape_data)
{
	t_shape *out;

	out = malloc(sizeof(t_shape));
	out->type = type;
	out->color = color;
	out->shape_data = shape_data;
	return (complete_shape(out));
}

t_shape
	*db_create_shape_list()
{
	t_shape *start;
	t_shape *elem;
	start = malloc(sizeof(t_shape));
	elem = start;
	//init
	elem->shape_data = (t_shapes) new_sphere(new_v3f(0, 0, -1000), 50);
	elem->type = SPHERE;
	elem->color = new_color(85, 42, 212);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(30, 0, -980), 30);
	elem->type = SPHERE;
	elem->color = new_color(161, 60, 232);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(25, 30, -500), 10);
	elem->type = SPHERE;
	elem->color = new_color(0, 0, 255);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	return start;
}

t_scene
	*get_scene(void)
{
	static t_scene scene;
	return (&scene);
}

void
	get_scene_info(int fd)
{
	char *line;
	t_scene *scene;

	scene = get_scene();
	while (get_next_line(fd, &line))
	{
		if (*line == 'R')
			scene->resolution = get_res(line);
		else if (*line == 'A')
			scene->light = get_light(line);
		else if (!ft_strncmp("c ", line, 2))
			scene->camera = mom_get_camera(line);
		else if (*line == 's')
			;
		free(line);
	}
	db_print_scene(*scene);
}

t_sdist tmin(t_shape *shape_list, t_ray ray)
{
	t_sdist sdist;
	float t;

	sdist.distance = 0;
	while (shape_list)
	{
		t = shape_list->calculate_fun.collision(*shape_list, ray);
		if ((sdist.distance == 0 || sdist.distance > t) && !isnan(t))
			sdist = (t_sdist) {.shape = *shape_list, .distance = t};
		shape_list = shape_list->next;
	}
	return (sdist);
}

int calculate_color(t_ray ray)
{
	t_v3float	normal;
	t_v3float	lerp;
	t_sdist		closest_shape;
	float		t;
	t_shape *shape_list = db_create_shape_list();
	t_light light = new_light(new_v3f(50, 0, -950), 1, new_color(255, 255, 255));

	closest_shape = tmin(shape_list, ray);
	if (closest_shape.distance != 0)
	{
		normal = shape_list->calculate_normal(closest_shape.distance, closest_shape.shape,ray);
		lerp.x = lerp_light(light, normal, ray_point_at(ray, closest_shape.distance));
		if ((lerp.x > 1 || lerp.x < 0))
			printf("%f\n", lerp.x);
		return (get_color(col_multiply(closest_shape.shape.color, lerp.x)));
	}
	t = 1 - (ray.direction.y + 1) * 0.5f;
	lerp = v3f_add(v3f_multiply_x(new_v3f(1, 1, 1), 1.0f - t),
	v3f_multiply_x(new_v3f(0.5f, 0.7f, 1.0f), t));
	return get_color_i((unsigned char)255.99 * lerp.x, (unsigned char)255.99 * lerp.y, (unsigned char)255.99 * lerp.z);
}

int window_test()
{
	void *mlx_ptr;
	void *window;
	int nx = 800;
	int ny = 400;

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, nx, ny, "Magic");
	t_v3float low_left = new_v3f(-2, -1, -10);
	t_v3float horizontal = new_v3f(4, 0, 0);
	t_v3float vertical = new_v3f(0, 2, 0);
	t_v3float origin = new_v3f(0, 0, 0);
	for (int j = ny - 1; j >= 0; j--)
		for (int i = 0; i < nx; i++)
		{
			float u = (float)i / (float)nx;
			float v = (float)j / (float)ny;
			t_ray r = new_ray(origin, v3f_add(v3f_add(low_left, v3f_multiply_x(horizontal, u)),
			v3f_multiply_x(vertical, v)));
			int color = calculate_color(r);
			mlx_pixel_put(mlx_ptr, window, i, j, color);
		}
	mlx_loop(mlx_ptr);
	return 0;
}

int main(int ac, char **av)
{
	int fd;

	window_test();
	if (ac <= 1)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(-1);
	get_scene_info(fd);
}