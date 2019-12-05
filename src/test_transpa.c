SDL_Surface *surface;
Uint32 *tmp;

surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
tmp = (Uint32 *)surface->pixels;
tmp[0] = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
tmp[1] = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
tmp[2] = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
tmp[3] = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
surface->pixels = (void *)tmp;
put_surface(ren, surface, create_sdl_rect(0,0,0,0));
