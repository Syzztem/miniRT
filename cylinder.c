/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lothieve <lothieve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 13:30:26 by lothieve          #+#    #+#             */
/*   Updated: 2020/08/07 14:53:58 by lothieve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_v3double
	calculate_cylinder_normal(double f, t_shape shape, t_ray ray)
{
	t_cylinder	cy;
	t_v3double	r;
	t_v3double	n;
	double		caoc;

	cy = shape.shape_data.cylinder;
	caoc = v3f_dot(cy.ca, v3f_sub(ray.origin, cy.pos));
	caoc += f * v3f_dot(cy.ca, ray.direction);
	if (!(caoc < cy.caca))
		return (shape.shape_data.cylinder.orientation);
	else
	{
		r = ray_point_at(ray, f);
		n = v3f_sub(r, cy.pos);
		n = v3f_cross(n, cy.orientation);
		n = v3f_normalize(v3f_cross(n, cy.orientation));
		return (n);
	}
}

static double
	cy_cap(t_v3double poly, t_v3double tyh)
{
	if (fabs(poly.y + poly.x * tyh.x) < tyh.z)
		return (tyh.x);
	return (nan(""));
}

double
	cy_col_2(t_cylinder cy, t_ray ray, t_v3double oc, double card)
{
	t_v3double	poly;
	t_v3double	tyh;
	double		caoc;

	caoc = v3f_dot(cy.ca, oc);
	poly.x = cy.caca - card * card;
	poly.y = cy.caca * v3f_dot(oc, ray.direction) - caoc * card;
	poly.z = cy.caca * v3f_dot(oc, oc) - caoc * caoc - cy.radius
		* cy.radius * cy.caca;
	tyh.z = poly.y * poly.y - poly.x * poly.z;
	if (tyh.z < 0.0)
		return (nan(""));
	tyh.z = sqrt(tyh.z);
	tyh.x = (-poly.y - tyh.z) / poly.x;
	tyh.y = caoc + tyh.x * card;
	if (tyh.y > 0.0 && tyh.y < cy.caca)
		return (tyh.x);
	tyh.x = (((tyh.y < 0.0) ? 0.0 : cy.caca) - caoc) / card;
	return (cy_cap(poly, tyh));
}

double
	check_cylinder_collision(t_shape shape, t_ray line)
{
	t_cylinder	cy;
	t_v3double	oc;
	double		card;

	cy = shape.shape_data.cylinder;
	oc = v3f_sub(line.origin, cy.capa);
	card = v3f_dot(cy.ca, line.direction);
	return (cy_col_2(cy, line, oc, card));
}
