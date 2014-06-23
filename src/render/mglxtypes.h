/*
 *  The ManaPlus Client
 *  Copyright (C) 2012-2014  The ManaPlus Developers
 *
 *  This file is part of The ManaPlus Client.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RENDER_MGLXTYPES_H
#define RENDER_MGLXTYPES_H

#include "main.h"
#if defined(USE_OPENGL) && defined(USE_X11)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

#if defined(__GXX_EXPERIMENTAL_CXX0X__)
#include <cstdint>
#else
#include <stdint.h>
#endif

typedef void *(*glXCreateContext_t) (Display *dpy, XVisualInfo *vis,
    void *shareList, bool direct);
typedef void *(*glXGetCurrentContext_t) (void);
typedef void (*glXCreateContextAttribs_t) (Display *dpy, GLXFBConfig config,
    void *share_context, bool direct, const int *attrib_list);
typedef GLXFBConfig *(*glXChooseFBConfig_t) (Display *dpy, int screen,
    const int *attrib_list, int *nelements);

#endif  // USE_OPENGL
#endif  // RENDER_MGLXTYPES_H
