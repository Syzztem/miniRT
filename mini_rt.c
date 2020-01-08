/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/08 11:28:49 by lothieve         ###   ########.fr       */
/*                                                                            */
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
	elem->shape_data = (t_shapes) new_sphere(new_v3f(0, 0, -1000), 50);
	elem->type = SPHERE;
	elem->albedo = new_color(85, 42, 212);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(30, 0, -980), 30);
	elem->type = SPHERE;
	elem->albedo = new_color(161, 60, 232);
	elem->calculate_fun.collision = check_sphere_collisions;
	elem->calculate_normal = calculate_sphere_normal;
	elem->next = NULL;
	//new elem
	elem->next = malloc(sizeof(t_shape));
	elem = elem->next;
	elem->shape_data.sphere = new_sphere(new_v3f(250, 0, -1000), 100);
	elem->type = SPHERE;
	elem->albedo = new_color(0, 0, 255);
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

t_light *db_create_light_list()
{
	t_light *head;
	t_light *current;

	head = malloc(sizeof(t_light));
	current = head;
	*current = new_light(new_v3f(-900, 0, -800), 1, new_color(255, 255, 255));
	current->next = malloc(sizeof(t_light));
	current = current->next;
	*current = new_light(new_v3f(70, 0, -800), 1, new_color(255, 255, 255));
	current->next = NULL;
	return (head);
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

void db_print_vector(t_v3float v)
{
	printf("%f, %f, %f\n", v.x, v.y, v.z);
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

int calculate_color(t_ray ray)
{
	t_v3float	normal;
	t_v3float	lerp;
	t_sdist		closest_shape;
	float		t;
	t_shape *shape_list = db_create_shape_list();
	t_light *light_list = db_create_light_list();

	closest_shape = tmin(shape_list, ray);
	if (closest_shape.distance != 0)
	{
		normal = shape_list->calculate_normal(closest_shape.distance, closest_shape.shape,ray);
		return (lerp_light(light_list, new_ray(ray_point_at(ray, closest_shape.distance), normal),
		closest_shape.shape.albedo, shape_list));
	}
	t = 1 - (ray.direction.y + 1) * 0.5f;
	lerp = v3f_add(v3f_multiply_x(new_v3f(1, 1, 1), 1.0f - t),
	v3f_multiply_x(new_v3f(0.5f, 0.7f, 1.0f), t));
	return get_color_i((unsigned char)255.99 * lerp.x, (unsigned char)255.99 * lerp.y, (unsigned char)255.99 * lerp.z);
}

t_image	generate_image(int width, int height, void *mlx_ptr)
{
	t_image out;

	out.img_ptr = mlx_new_image(mlx_ptr, width, height);
	out.width = width;
	out.height = height;
	out.img_data = (int *) mlx_get_data_addr(out.img_ptr, (int *) &out.bpp, &out.size_line, &out.endian);
	return (out);
}

void	image_pixel_put(t_image image, int x, int y, int color)
{
	image.img_data[x + y * image.size_line / sizeof(int)] = color;
}

int window_test()
{
	void *mlx_ptr;
	void *window;
	int nx = 1600;
	int ny = 800;

	mlx_ptr = mlx_init();
	t_image image;
	image  = generate_image(nx, ny, mlx_ptr);
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
			image_pixel_put(image, i, j, color);
		}
	create_bitmap(image, "test.bmp");
	mlx_put_image_to_window(mlx_ptr, window, image.img_ptr, 0, 0);
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