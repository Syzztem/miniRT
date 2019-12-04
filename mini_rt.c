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
	print_scene(t_scene s)
{
	printf("Scene:\nResolution : %d %d\nAmbient light : Intensity: %.3f, Color: %x\nCamera: position: %d,%d,%d rotation: %.3f,%.3f,%.3f angle: %d",
	s.resolution.x, s.resolution.y, s.light.intensity, s.light.color, s.camera.pos.x, s.camera.pos.y, s.camera.pos.z, s.camera.rot.x, s.camera.rot.y, s.camera.rot.z, s.camera.fov);
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
	print_scene(*scene);
}

int color_from_ray(t_ray r)
{
	t_v3float normal;
	t_v3float lerp;
	float t;

	t = check_sphere_collisions(r, new_sphere(new_v3f(0, 0, -1), 0.5f));
	if (!isnan(t))
	{
		normal = v3f_normalize(v3f_substract_v(ray_point_at(r, t), new_v3f(0, 0, -1)));
		lerp = v3f_multiply_x(v3f_add(normal, new_v3f(1, 1, 1)), 0.5f);
		return get_color_i(
			(unsigned char)255 * lerp.x,
			(unsigned char)255 * lerp.y,
			(unsigned char)255 * lerp.z);
	}
	t = 1 - (r.direction.y + 1) * 0.5f;
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
	t_v3float low_left = new_v3f(-2, -1, -1);
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
			int color = color_from_ray(r);
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