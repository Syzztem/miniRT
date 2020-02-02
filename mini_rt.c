/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/02 15:06:02 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "get_next_line.h"

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
	char	*line;
	t_scene	scene;

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
		else if (*line == 'c' && ft_isspace(*(line + 1)))
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
	return (scene);
}

int
	mini_rt(t_scene scene, int savemode, char *filename)
{
	void	*mlx_ptr;
	void	*window;

	mlx_ptr = mlx_init();
	trace(scene, generate_image(scene.resolution, mlx_ptr));
	if (!savemode)
	{
		window = mlx_new_window(mlx_ptr, scene.resolution.x,
			scene.resolution.y, filename);
		mlx_put_image_to_window(mlx_ptr, window,
			scene.camera->render.img_ptr, 0, 0);
		mlx_key_hook(window, k_hook, &scene);
		mlx_hook(window, 17, 0, xyeet, &scene);
		scene.mlx_pointer = mlx_ptr;
		scene.window_pointer = window;
		mlx_loop(mlx_ptr);
	}
	create_bitmap(scene.camera->render, filename);
	return (0);
}

int
	main(int ac, char **av)
{
	int		fd;
	t_scene	test_scene;
	int		savemode;
	int		i;
	char	*filename;

	i = 0;
	savemode = 0;
	if (ac <= 1)
		return (-1);
	while (++i < ac)
	{
		if (!ft_strncmp(av[i], "--save", 6))
			savemode = 1;
		else
			filename = av[i];
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	test_scene = get_scene_info(fd);
	mini_rt(test_scene, savemode, basename(filename));
}
