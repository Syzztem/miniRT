/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 17:17:21 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/03 14:49:05 by lothieve         ###   ########.fr       */
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
	parse_line(char *line, t_scene scene)
{
	if (*line == 'R')
		scene.resolution = scene.resolution.x == -1 ? get_res(line) :
			(t_vector2){.x = -1, .y = -1};
	else if (*line == 'A')
		scene.ambient_light = scene.ambient_light.intensity == -1 ?
			get_alight(line) : (t_alight)
			{.intensity = -1, .color = new_color(0, 0, 0)};
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
	return (scene);
}

t_scene
	get_scene_info(int fd)
{
	char	*line;
	t_scene	scene;

	scene.camera = NULL;
	scene.shape_list = NULL;
	scene.light_list = NULL;
	scene.resolution = (t_vector2){.x = -1, .y = -1};
	scene.ambient_light.intensity = -1;
	while (get_next_line(fd, &line))
		scene = parse_line(line, scene);
	finish_cam_list(scene.camera);
	if (scene.resolution.x > MAX_RES_X)
		scene.resolution = (t_vector2){
			.x = MAX_RES_X,
			.y = (float)scene.resolution.y
			* ((float)MAX_RES_X / (float)scene.resolution.x) - 0.5f};
	if (scene.resolution.y > MAX_RES_Y)
		scene.resolution = (t_vector2){
			.x = (float)scene.resolution.x * ((float)MAX_RES_Y /
			(float)scene.resolution.y) - 0.5f, .y = MAX_RES_Y};
	if (scene.ambient_light.intensity == -1 || scene.resolution.x == -1
		|| !scene.camera || !scene.light_list || !scene.shape_list
		|| g_error != 0)
		yeet(scene, 1, "Error\n invalid file\n");
	return (scene);
}

void
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
	yeet(scene, 0, NULL);
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
	g_error = 0;
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
	if (ft_strncmp(filename + ft_strlen(filename) - 3, ".rt", 3))
		return (ft_puts("Error\nBad file extension.\n", -1));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_puts("Error\nCouldn't open file.\n", -1));
	test_scene = get_scene_info(fd);
	mini_rt(test_scene, savemode, filename);
}
