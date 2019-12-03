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

int window_test()
{
	void *mlx_ptr;
	void *window;
	t_sphere sphere;
	t_line line;

	mlx_ptr = mlx_init();
	window = mlx_new_window(mlx_ptr, 500, 500, "Magic");
	sphere.center = new_v3f(100, 100, 100);
	sphere.radius = 20;
	line.origin = new_v3f(-20, -20, -20);
	t_v3float cam_dir = v3f_normalize(new_v3f(1, 1, 1));
	t_v3float center_screen = v3f_multiply_x(cam_dir, 70 /*FOV*/);
	t_v3float c_s = v3f_substract_v(center_screen, line.origin);
	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
		{
			t_v3float point_on_screen = v3f_add(new_v3f(i - 250, j - 250, 0), c_s);
			line.direction = v3f_normalize(v3f_substract_v(line.origin, point_on_screen));
			if (!isnan(check_sphere_collisions(line, sphere)))
				mlx_pixel_put(mlx_ptr, window, i, j, 0x0);
			else
				mlx_pixel_put(mlx_ptr, window, i, j, 0x00ffffff);
		}
	mlx_loop(mlx_ptr);
	t_v3float p = v3f_add(line.origin, v3f_multiply_x(line.direction, check_sphere_collisions(line, sphere)));
	printf("%f, %f, %f\n", p.x, p.y, p.z);
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