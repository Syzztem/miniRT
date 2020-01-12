/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/12 13:50:27 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "get_next_line.h"

void db_print_vector(t_v3float v)
{
	printf("%f, %f, %f\n", v.x, v.y, v.z);
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
	out->albedo = color;
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
	elem->shape_data = (t_shapes) new_sphere(new_v3f(0, 0, 1000), 100);
	elem->type = SPHERE;
	elem->albedo = new_color(85, 42, 212);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(60, 200, 980), 60);
	elem->type = SPHERE;
	elem->albedo = new_color(161, 60, 232);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(500, 0, 1000), 200);
	elem->type = SPHERE;
	elem->albedo = new_color(0, 0, 255);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;

	return start;
}

t_light *db_create_light_list()
{
	t_light *head;
	t_light *current;

	head = malloc(sizeof(t_light));
	current = head;
	*current = new_light(new_v3f(-900, 0, 800), 1, new_color(255, 255, 255));
	current->next = malloc(sizeof(t_light));
	current = current->next;
	*current = new_light(new_v3f(70, 0, 800), 1, new_color(255, 255, 255));
	current->next = NULL;
	return (head);
}

void
	get_scene_info(int fd)
{
	char *line;
	t_scene scene;

	while (get_next_line(fd, &line))
	{
		if (*line == 'R')
			scene.resolution = get_res(line);
		else if (*line == 'A')
			scene.ambient_light = get_light(line);
		else if (!ft_strncmp("c ", line, 2))
			scene.camera = mom_get_camera(line);
		else if (*line == 's')
			;
		free(line);
	}
	scene.shape_list = db_create_shape_list();
	scene.light_list = db_create_light_list();
}

t_sdist tmin(t_shape *shape_list, t_ray ray)
{
	t_sdist sdist;
	float t;

	sdist.distance = 0;
	while (shape_list)
	{
		t = shape_list->calculate_fun.collision(*shape_list, ray);
		if ((sdist.distance == 0 || sdist.distance > t) && !isnan(t) && t > 0)
			sdist = (t_sdist) {.shape = *shape_list, .distance = t};
		shape_list = shape_list->next;
	}
	return (sdist);
}

int calculate_color(t_ray ray, t_scene scene)
{
	t_v3float	normal;
	t_v3float	lerp;
	t_sdist		closest_shape;
	float		t;

	closest_shape = tmin(scene.shape_list, ray);
	if (closest_shape.distance != 0)
	{
		normal = scene.shape_list->calculate_normal(closest_shape.distance, closest_shape.shape,ray);
		return (lerp_light(scene.light_list, new_ray(ray_point_at(ray, closest_shape.distance), normal),
			closest_shape.shape.albedo, scene));
	}
	t = 1 - (ray.direction.y + 1) * 0.5f;
	lerp = v3f_add(v3f_multiply_x(new_v3f(1, 1, 1), 1.0f - t),
	v3f_multiply_x(new_v3f(0.5f, 0.7f, 1.0f), t));
	return (0);
	return get_color_i((unsigned char)255.99 * lerp.x, (unsigned char)255.99 * lerp.y, (unsigned char)255.99 * lerp.z);
}

t_image	generate_image(t_vector2 res, void *mlx_ptr)
{
	t_image out;

	out.img_ptr = mlx_new_image(mlx_ptr, res.x, res.y);
	out.res = res;
	out.img_data = (int *) mlx_get_data_addr(out.img_ptr, (int *) &out.bpp, &out.size_line, &out.endian);
	return (out);
}

void	image_pixel_put(t_image image, int x, int y, int color)
{
	image.img_data[x + y * image.size_line / sizeof(int)] = color;
}

t_image
	trace(t_scene scene, t_image image)
{
	int		i;
	int		j;
	float	dist_to_screen;
	t_ray	r;

	dist_to_screen = scene.resolution.x / (2 * tanf(DEG_TO_RAD * scene.camera->fov / 2));
	i = 0;
	while (i < scene.resolution.x)
	{
		j = 0;
		while (j < scene.resolution.y)
		{
			r = ray_from_points(scene.camera->pos, new_v3f(-i + scene.resolution.x / 2, j - scene.resolution.y / 2, -dist_to_screen));
			r.direction = v3f_rotate(r.direction, scene.camera->rot_data.axe, scene.camera->rot_data.r_sin, scene.camera->rot_data.r_cos);
			image_pixel_put(image, i, j, calculate_color(r, scene));
			j++;
		}
		i++;
	}
	scene.camera->render = image;
	return (image);
}

int	mini_rt(t_scene scene)
{
	void	*mlx_ptr;
	void	*window;
	//t_image	image;
	
	mlx_ptr = mlx_init();
	trace(scene, generate_image(scene.resolution, mlx_ptr));
	window = mlx_new_window(mlx_ptr, scene.resolution.x, scene.resolution.y, "Magic");
	mlx_put_image_to_window(mlx_ptr, window, scene.camera->render.img_ptr, 0, 0);
	mlx_key_hook(window, k_hook, &scene);
	scene.mlx_pointer = mlx_ptr;
	scene.window_pointer = window;
	mlx_loop(mlx_ptr);
	return (0);
}

int main(int ac, char **av)
{
	int fd;
	t_scene test_scene;

	//window_test();
	test_scene.resolution = (t_vector2) {.x = 1600, .y = 800};
	test_scene.camera = malloc(sizeof(t_cam));
	test_scene.camera->pos = new_v3f(0, 0, 0);
	test_scene.camera->rot = v3f_normalize(new_v3f(0.2f, 0.3f, 0.7f));
	test_scene.camera->fov = 90;
	calculate_rotation_data(test_scene.camera);
	printf("%f, %f\n", test_scene.camera->rot_data.r_cos, test_scene.camera->rot_data.r_sin);
	db_print_vector(test_scene.camera->rot_data.axe);
	test_scene.ambient_light = (t_alight) {.intensity = 0.2f, .color = new_color(255, 255, 255)};
	test_scene.shape_list = db_create_shape_list();
	test_scene.light_list = db_create_light_list();
	mini_rt(test_scene);
	return 0;
	if (ac <= 1)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(-1);
	get_scene_info(fd);
}
