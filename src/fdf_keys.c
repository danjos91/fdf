/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nshelly <nshelly@student.21school.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 04:45:57 by nshelly           #+#    #+#             */
/*   Updated: 2019/08/30 04:54:52 by nshelly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** **************************************************************************
**    int fdf_keys(int key, void *param)
**    Function which allow users to control FdF with keyboard
** numbers  : keys
** 0xff51,0xff53 : Left,Right arrows
** 0x006a,0x006b : j,k
** 0x0075,0x0069 : u,i
** 0xff52,0xff54 : Up,Down arrows
** 0x002b,0x003d,0x002d : +,=,-
** 0x0071,0x0065 : q, e
** 0x0064,0x0061 : d, a
** 0x0077,0x0073 : w, s
** 0x0020 : space
** 0x0063,0x0076 : c, v
** 0xff1b : esc
** **************************************************************************
*/

static void	fdf_more_keys(int key, t_w *new_w)
{
	if (key == 0xff52 || (key == 0xff54 && new_w->m > 1))
		new_w->m = key == 0xff52 ? (new_w->m + 1) : (new_w->m - 1);
	if (key == 0x002b || key == 0x003d || key == 0x002d)
		new_w->mv_z = key == 0x002d ? new_w->mv_z + 5 : new_w->mv_z - 5;
	if (key == 0x0071 || key == 0x0065)
		new_w->mv_z2 = key == 0x0071 ? new_w->mv_z2 + 10 : new_w->mv_z2 - 10;
	if (key == 0x0064 || key == 0x0061)
		new_w->mv_x = key == 0x0064 ? new_w->mv_x + 10 : new_w->mv_x - 10;
	if (key == 0x0077 || key == 0x0073)
		new_w->mv_y = key == 0x0077 ? new_w->mv_y - 10 : new_w->mv_y + 10;
	if (key == 0x0020)
		fdf_initials(new_w);
	if (key == 0x0063 || key == 0x0076)
	{
		if (key == 0x0063)
			fdf_color_change(new_w);
		else
		{
			new_w->color_style = (new_w->color_style + 1) % 10;
			fdf_change_color(new_w);
		}
	}
	if (key == 0xff1b)
		exit(0);
}

int			fdf_keys(int key, void *param)
{
	t_w		*new_w;
	double	a;

	a = 5 * (M_PI / 180);
	new_w = (t_w *)param;
	if (key == 0xff51 || key == 0xff53)
		new_w->angle = key == 0xff51 ? (new_w->angle + a) : (new_w->angle - a);
	if (key == 0x006a || key == 0x006b)
	{
		new_w->angle_x = key == 0x006a ? (new_w->angle_x + a) :\
			(new_w->angle_x - a);
	}
	if (key == 0x0075 || key == 0x0069)
	{
		new_w->angle_y = key == 0x0075 ? (new_w->angle_y + a) : \
			(new_w->angle_y - a);
	}
	fdf_more_keys(key, new_w);
	fdf_redraw(new_w);
	return (0);
}
