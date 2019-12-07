# define TEXT_WALL_HEIGHT	10
# define TEXT_WALL_WIDTH	10

void	calc_z(t_work *work, int x)
{
	work->z = ((x - work->x1) * (work->t2.z - work->t1.z) / (work->x2 - work->x1) + work->t1.z) * 2;
	work->z = vmin(work->z, 255);
}

int		dark_side(int color, t_work *work)
{
	int red;
	int gre;
	int blu;

	red = vmid((((color >> 16) & 0xff) - (work->z / 2)), 0, 255);
	gre = vmid((((color >> 8) & 0xff) - (work->z / 2)), 0, 255);
	blu = vmid((((color) & 0xff) - (work->z / 2)), 0, 255);
	return (0 << 24 | (red & 0xff) << 16 | (gre & 0xff) << 8 | (blu & 0xff));
}

void	draw_textured_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	while (d->y1 <= d->y2)
	{
		d->y_tex = (d->y_tex_pos / d->wall_height_from_bottom * d->wall_height_scale) * text->h;
		if (d->y_tex < 0)
			d->y_tex = 0;
		if (d->x_tex < 0)
			d->x_tex = 0;
		if (text->h >= 0 && text->w >= 0 && text->pix[((d->y_tex % text->h) * text->w) + (d->x_tex % text->w)] != TRANSPARENT)
		{
			d->color = text->pix[((d->y_tex % text->h) * text->w) + (d->x_tex % text->w)];
			d->color = dark_side(d->color, work);
			w->pix[d->y1 * WIDTH + d->x] = d->color;
		}
		d->y_tex_pos++;
		d->y1++;
	}
}

void	check_start_end_tex(t_draw *d, t_work *work, t_texture *text)
{
	if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
	{
		work->start_x_tex = (work->t1.x - work->tt1.x) * text->w / d->wall_width_scale / (work->tt2.x - work->tt1.x);
		work->end_x_tex = (work->t2.x - work->tt1.x) * text->w / d->wall_width_scale / (work->tt2.x - work->tt1.x);
	}
	else
	{
		work->start_x_tex = (work->t1.z - work->tt1.z) * text->w / d->wall_width_scale / (work->tt2.z - work->tt1.z);
		work->end_x_tex = (work->t2.z - work->tt1.z) * text->w / d->wall_width_scale / (work->tt2.z - work->tt1.z);
	}
}

void	do_normal_wall_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	d->wall_height_from_bottom = work->yb - work->starty;
	d->wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
	d->wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
	check_start_end_tex(d, work, text);
	d->y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1) - (d->x - work->x1)) / (work->x2 - work->x1) - work->y2a;
	d->x_tex = ((work->start_x_tex * ((work->x2 - d->x) * work->t2.z)
		+ work->end_x_tex * ((d->x - work->x1) * work->t1.z)) / ((work->x2
			- d->x) * work->t2.z + (d->x - work->x1) * work->t1.z));
	if ((work->y1a < 0 || work->y2a < 0) && d->y1 == 0)
	{
		d->wall_height_from_bottom += d->y_tex_start;
		d->y_tex_pos += d->y_tex_start;
		draw_textured_line(d, w, work, text);
	}
	else
	{
		d->wall_height_from_bottom = work->yb - work->ya;
		draw_textured_line(d, w, work, text);
	}
}

void	do_special_wall_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	d->wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
	d->wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
	d->wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
	check_start_end_tex(d, work, text);
	d->y_tex_start = (work->starty - work->ya);
	d->x_tex = ((work->start_x_tex * ((work->x2 - d->x) * work->t2.z) + work->end_x_tex * ((d->x - work->x1) * work->t1.z)) / ((work->x2 - d->x) * work->t2.z + (d->x - work->x1) * work->t1.z));
	d->wall_height_from_bottom += d->y_tex_start;
	d->y_tex_pos += d->y_tex_start;
	draw_textured_line(d, w, work, text);
}


void	draw_wall_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_draw	d;

	d.x = x;
	d.y_tex_pos = 0;
	d.y1 = vmid(work->starty, 0, HEIGHT - 1);
	d.y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (d.y2 > d.y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == d.y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
			do_special_wall_line(&d, w, work, text);
		else
			do_normal_wall_line(&d, w, work, text);
	}
}

void	draw_walls(t_work *work, t_env *w, int x)
{
	work->starty = work->cya;
	work->stopy = work->cyb;
	// if (w->texturing[w->m->sector[work->nosector].texturing[2]].trsp == 1)
	// {
	// 	skybox(x, w, work,
	// 		w->texturing[w->m->sector[work->nosector].texturing[5]]);
	// 	draw_wall_line_t(x, w, work,
	// 		&w->texturing[w->m->sector[work->nosector].texturing[2]]);
	// }
	// else
	draw_wall_line_t(x, w, work, &w->texturing[w->m->sector[work->nosector].texturing[2]]);
}

void	calcul_render_no_mthrd(t_env *w, t_work *work)
{
	int x;

	x = work->startx;
	while (x <= work->endx)
	{
		calc_z(work, x);
		draw_ceiling_n_floor(work, w, x);
		if (work->network >= 0)
		{
			draw_networks(work, w, x);
			work->ytop[x] = vmid(vmax(work->cya, work->cnya), work->ytop[x], HEIGHT - 1);
			work->ybot[x] = vmid(vmin(work->cyb, work->cnyb), 0, work->ybot[x]);
		}
		else
			draw_walls(work, w, x);
		x++;
	}
}
