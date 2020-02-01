/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/01/21 16:55:42 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "get_next_line.h"

void db_print_vector(t_v3float v)
{
	printf("%.2f, %.2f, %.2f\n", v.x, v.y, v.z);
}

void db_print_color(t_color c)
{
	printf("r%d, g%d, b%d\n", c.r, c.g, c.b);
}

void
	finish_cam_list(t_cam *cam_list)
{
	t_cam *start;
	t_cam *end;

	start = cam_list;
	end = cam_list;
	while (end->next)
		end = end->next;
	end->next = start;
}

t_scene
	get_scene_info(int fd)
{
	char *line;
	t_scene scene;

	scene.camera = NULL;
	scene.shape_list = NULL;
	scene.light_list = NULL;
	while (get_next_line(fd, &line))
	{
		if (*line == 'R')
			scene.resolution = get_res(line);
		else if (*line == 'A')
			scene.ambient_light = get_alight(line);
		else if (*line == 'l')
			add_light(line, &scene.light_list);
		else if (*line == 'c' && ft_isspace(*(line +1)))
			add_cam(line, &scene.camera);
		else if (!ft_strncmp("sp", line, 2))
			add_sphere(line, &scene.shape_list);
		else if (!ft_strncmp("pl", line, 2))
			add_plane(line, &scene.shape_list);
		else if (!ft_strncmp("cy", line, 2))
			add_cylinder(line, &scene.shape_list);
		else if (!ft_strncmp("tr", line, 2))
			add_triangle(line, &scene.shape_list);
		else if (!ft_strncmp("sq", line, 2))
			add_square(line, &scene.shape_list);
		free(line);
	}
	finish_cam_list(scene.camera);
	return(scene);
}

t_sdist tmin(t_shape *shape_list, t_ray ray)
{
	t_sdist sdist;
	float t;

	sdist.distance = 0;
	while (shape_list)
	{
		t = shape_list->calculate_fun.collision(*shape_list, ray);
		if ((sdist.distance == 0 || sdist.distance > t) && !isnan(t) && t > EPSILON)
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
		normal = closest_shape.shape.calculate_normal(closest_shape.distance, closest_shape.shape, ray);
		if (v3f_dot(ray.direction, normal) > 0)
			normal = v3f_multiply_x(normal, -1);
		return (lerp_light(scene.light_list, new_ray(ray_point_at(ray, closest_shape.distance), normal),
			closest_shape.shape, scene, closest_shape.distance));
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

void
	next_view(t_scene *scene)
{
	scene->camera = scene->camera->next;
	if (!scene->camera->render.img_data)
	{
		scene->camera->render = generate_image(scene->resolution, scene->mlx_pointer);
		trace(*scene, scene->camera->render);
	}
	mlx_put_image_to_window(scene->mlx_pointer, scene->window_pointer, scene->camera->render.img_ptr, 0, 0);
}

int	mini_rt(t_scene scene)
{
	void	*mlx_ptr;
	void	*window;
	
	mlx_ptr = mlx_init();
	trace(scene, generate_image(scene.resolution, mlx_ptr));
	window = mlx_new_window(mlx_ptr, scene.resolution.x, scene.resolution.y, "Magic");
	mlx_put_image_to_window(mlx_ptr, window, scene.camera->render.img_ptr, 0, 0);
	mlx_key_hook(window, k_hook, &scene);
	scene.mlx_pointer = mlx_ptr;
	scene.window_pointer = window;
//	create_bitmap(scene.camera->render, "cool_pic.bmp");
	mlx_loop(mlx_ptr);
	return (0);
}

int main(int ac, char **av)
{
	int fd;
	t_scene test_scene;

	if (ac <= 1)
		return (-1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(-1);
	test_scene = get_scene_info(fd);
	mini_rt(test_scene);
}
