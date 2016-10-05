# Copyright (C) 2012, Naomasa Matsubayashi
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# - Find libdl
# Find the native LIBDL includes and library
#
#  LIBDL_INCLUDE_DIR - where to find dlfcn.h, etc.
#  LIBDL_LIBRARIES   - List of libraries when using libdl.
#  LIBDL_FOUND       - True if libdl found.

IF (LIBDL_INCLUDE_DIR)
  # Already in cache, be silent
  SET(LIBDL_FIND_QUIETLY TRUE)
ENDIF (LIBDL_INCLUDE_DIR)

FIND_PATH(LIBDL_INCLUDE_DIR dlfcn.h)

SET(LIBDL_NAMES dl libdl ltdl libltdl)
FIND_LIBRARY(LIBDL_LIBRARY NAMES ${LIBDL_NAMES} )

# handle the QUIETLY and REQUIRED arguments and set LIBDL_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibDL DEFAULT_MSG LIBDL_LIBRARY LIBDL_INCLUDE_DIR)

IF(LIBDL_FOUND)
  SET( LIBDL_LIBRARIES ${LIBDL_LIBRARY} )
ELSE(LIBDL_FOUND)
  SET( LIBDL_LIBRARIES )
ENDIF(LIBDL_FOUND)

MARK_AS_ADVANCED( LIBDL_LIBRARY LIBDL_INCLUDE_DIR )
