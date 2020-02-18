/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:30:26 by lothieve          #+#    #+#             */
/*   Updated: 2020/02/18 10:17:32 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_v3double
	get_cylinder_normal(double f, t_cylinder cy, t_ray ray)
{
	t_v3double	hb;
	t_v3double	out;

	hb = v3f_sub(ray_point_at(ray, f), cy.pos);
	hb = v3f_cross(cy.orientation, hb);
	out = v3f_cross(cy.orientation, hb);
	return (v3f_normalize(out));
}

t_v3double calculate_cylinder_normal(double f, t_shape shape, t_ray ray)
{
	(void) f;
	(void) ray;
	return (*shape.shape_data.cylinder.normal);
}

double
	cap_cylinder(t_cylinder cy, t_ray ray, double dist)
{
	double hitdist;
	double cad;
	double cbd;

	if (isnan(dist))
		return (dist);
	hitdist = v3f_magnitude(v3f_sub(ray_point_at(ray, dist), cy.pos));
	if (hitdist < cy.dh_radius)
	{
		*cy.normal = get_cylinder_normal(hitdist, cy, ray);
		return (hitdist);
	}
	cad = plane_intersecton(new_plane(cy.orientation, cy.capa), ray);
	cbd = plane_intersecton(new_plane(cy.orientation, cy.capb), ray);
	dist = ft_fminpos(cad, cbd);
	if (isnan(dist))
		return (dist);
	hitdist = v3f_magnitude(v3f_sub(ray_point_at(ray, dist), dist == cad ? cy.capa : cy.capb));
	if (hitdist <= cy.radius)
	{
		*cy.normal = cy.orientation;
		return (dist);
	}
	return (nan(""));
}

/*
double
	check_cylinder_collision(t_shape shape, t_ray line)
{
	t_cylinder c;

	c = shape.shape_data.cylinder;
		return (cap_cylinder(c, line, solve_quadra(line.direction.x * line.direction.x + line.direction.y * line.direction.y + line.direction.z *
	line.direction.z - (((c.orientation.x * line.direction.x + c.orientation.y * line.direction.y + c.orientation.z * line.direction.z) * (c.orientation.x *
	line.direction.x + c.orientation.y * line.direction.y + c.orientation.z * line.direction.z)) / (c.orientation.x * c.orientation.x +
	c.orientation.y * c.orientation.y + c.orientation.z * c.orientation.z)), 2 * ((line.origin.x - c.pos.x
	) * line.direction.x + (line.origin.y - c.pos.y) * line.direction.y + (line.origin.z - c.pos.z) * line.direction.z) -
	((2 * (c.orientation.x * (line.origin.x - c.pos.x) + c.orientation.y * (line.origin.y - c.pos.y) +
	c.orientation.z * (line.origin.z - c.pos.z)) * (c.orientation.x * line.direction.x + c.orientation.y * line.direction.y +
	c.orientation.z * line.direction.z)) / (c.orientation.x * c.orientation.x + c.orientation.y * c.orientation.y +
	c.orientation.z * c.orientation.z)), (line.origin.x - c.pos.x) * (line.origin.x - c.pos.x) +
	(line.origin.y - c.pos.y) * (line.origin.y - c.pos.y) + (line.origin.z - c.pos.z) *
	(line.origin.z - c.pos.z) - (((c.orientation.x * (line.origin.x - c.pos.x) + c.orientation.y *
	(line.origin.y - c.pos.y) + c.orientation.z * (line.origin.z - c.pos.z)) * (c.orientation.x *
	(line.origin.x - c.pos.x) + c.orientation.y * (line.origin.y - c.pos.y) + c.orientation.z *
	(line.origin.z - c.pos.z))) / (c.orientation.x * c.orientation.x + c.orientation.y * c.orientation.y +
	c.orientation.z * c.orientation.z)) - c.radius * c.radius)));
}
*/

double
	check_cylinder_collision(t_shape shape, t_ray line)
{
	t_cylinder cy = shape.shape_data.cylinder;
	t_v3double delta = v3f_sub(line.origin, cy.pos);
	t_v3double ldot = v3f_sub(line.direction, v3f_multiply(cy.orientation, v3f_dot(line.direction, cy.orientation)));
	t_v3double ddot = v3f_sub(delta, v3f_multiply(cy.orientation, v3f_dot(delta, cy.orientation)));
	double a = v3f_square(ldot);
	double b = 2.0f * v3f_dot(ldot, ddot);
	double c = v3f_square(ddot) - square(cy.radius);
	//return (solve_quadra(a, b, c));
	return(cap_cylinder(cy, line, solve_quadra(a, b, c)));
}