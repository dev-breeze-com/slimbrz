// Brzdm - Breeze::OS Login/Display Manager
//
// Copyright (C) 2015 Tsert.Inc <contact@tsert.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
#ifndef _BRZDM_IMLIB_H_
#define _BRZDM_IMLIB_H_

#include <X11/Xlib.h>
#include <string>

extern "C" {
#include <Imlib2.h>
};


#define   CAST_IMAGE(im, image) ((im) = static_cast<ImlibImage*>(image))

#include "utils.h"
#include "config.h"

namespace breeze {

typedef struct RGBA { uint r; uint g; uint b; uint a; uint gradient; } RGBA;

class Imlib {
public:
	enum GradientType {
		LINEAR		= 0x0001,
		CIRCULAR	= 0x0002,
		VERTICAL	= 0x0004,
		HORIZONTAL	= 0x0008,
		HALVED		= 0x0010
	};

	enum Mode {
		NORMAL	= 0x0000,
		SCALE	= 0x0001,
		TILE	= 0x0002
	};

	enum Alignment {
		NOALIGN	= 0x0000,
		CENTER	= 0x0001,
		RIGHT	= 0x0002,
		LEFT	= 0x0004
	};

private:
	Imlib() {}
	Imlib(const Imlib&) {}
   ~Imlib() {}
	Imlib& operator=(const Imlib&) { return (*this); }

public:
	static void init(::Display *dpy, Config *themecfg);

	static void release();
	static void release(Imlib_Image image);
	static void clear(Imlib_Image image);

	static int width(Imlib_Image image);
	static int height(Imlib_Image image);

	//static bool merge(Imlib_Image dest, Imlib_Image src, int x, int y);

	static void setRGBA(const std::string& rgba, RGBA *rgb);

	static Imlib_Image rectangle(Imlib_Image image, const RGBA& rgb,
		int w, int h, bool shadow=false);

	static Imlib_Image gradient(Imlib_Image image, const std::string& gradtype,
		const RGBA& srgb, const RGBA& ergb, int w=0, int h=0);

	static Imlib_Image create(int w, int h, bool shadow=false);

	static Imlib_Image create(const std::string& path, int w=0, int h=0,
		bool shadow=false, bool with_cache=false);

	static Imlib_Image load(const std::string& path, bool with_cache=false);

	static Imlib_Image loadSized(const std::string& folder,
		const std::string& format);

	static void drawText(Imlib_Image image,
		const std::string& text, const std::string& font,
		const RGBA& rgba, int x, int y, Imlib::Alignment=Imlib::LEFT,
		Imlib_Text_Direction=IMLIB_TEXT_TO_RIGHT);

	static void draw(Imlib_Image image, ::Drawable win,
		int x=0, int y=0, int blend=1, RGBA *rgba=0L);

	static void scale(Imlib_Image image, ::Drawable win,
		int w, int h, int x=0, int y=0, int blend=1);

};

};

#endif /* _BRZ_Imlib_H_ */
