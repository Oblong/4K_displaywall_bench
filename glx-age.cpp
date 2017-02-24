/*
 * Copyright (c) 2017 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_GLX
#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <GL/glx.h>
#include <GL/glxext.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char* (*PFNGLXGETCLIENTSTRINGPROC)(Display*,int);
PFNGLXGETCLIENTSTRINGPROC           _glXGetClientString;
PFNGLXQUERYDRAWABLEPROC             _glXQueryDrawable;

static bool
extension_in_string(const char *exts, const char *ext)
{
  const char *pos = exts;
  const int len = strlen(ext);
  do {
    pos = strstr(pos, ext);
    if (!pos)
      return false;
    if ((pos == exts || *(pos-1) == ' ') &&
        (*(pos+len) == '\0' || *(pos+len) == ' ')) {
      return true;
    }
    pos = strchr(pos + len, ' ');
  } while (pos);

  return false;
}

static bool
buffer_age_supported(void)
{
  static bool checked = false;
  static bool supported = false;

  if (checked)
    return supported;

  Display *dpy = glfwGetX11Display();
  if (dpy != NULL) {
    _glXGetClientString = (PFNGLXGETCLIENTSTRINGPROC)
      glfwGetProcAddress("glXGetClientString");
    assert(_glXGetClientString);
    const char *ext = _glXGetClientString(dpy, GLX_EXTENSIONS);
    assert(ext);

    _glXQueryDrawable = (PFNGLXQUERYDRAWABLEPROC)
      glfwGetProcAddress("glXQueryDrawable");
    assert(_glXQueryDrawable);
    supported = extension_in_string(ext, "GLX_EXT_buffer_age");
  }

  checked = true;
  return supported;
}

int
buffer_age(GLFWwindow* window)
{
  if (!buffer_age_supported())
    return -1;
  Display *dpy = glfwGetX11Display();
  GLXWindow glxwin = glfwGetGLXWindow(window);
  unsigned int age;
  _glXQueryDrawable(dpy, glxwin, GLX_BACK_BUFFER_AGE_EXT, &age);
  return age;
}
