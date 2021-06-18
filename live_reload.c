/* Code from xst: https://github.com/gnotclub/xst */

int cursorblinkstate = 0;

#define XRESOURCE_LOAD_META(NAME)					\
	if(!XrmGetResource(xrdb, "st." NAME, "st." NAME, &type, &ret))	\
		XrmGetResource(xrdb, "*." NAME, "*." NAME, &type, &ret); \
	if (ret.addr != NULL && !strncmp("String", type, 64))

#define XRESOURCE_LOAD_STRING(NAME, DST)	\
	XRESOURCE_LOAD_META(NAME)		\
		DST = ret.addr;

#define XRESOURCE_LOAD_CHAR(NAME, DST)		\
	XRESOURCE_LOAD_META(NAME)		\
		DST = ret.addr[0];

#define XRESOURCE_LOAD_INTEGER(NAME, DST)		\
	XRESOURCE_LOAD_META(NAME)			\
		DST = strtoul(ret.addr, NULL, 10);

#define XRESOURCE_LOAD_FLOAT(NAME, DST)		\
	XRESOURCE_LOAD_META(NAME)		\
		DST = strtof(ret.addr, NULL);

void
xrdb_load(void)
{
	/* XXX */
	char *xrm;
	char *type;
	XrmDatabase xrdb;
	XrmValue ret;
	Display *dpy;

	if(!(dpy = XOpenDisplay(NULL)))
		die("Can't open display\n");

	XrmInitialize();
	xrm = XResourceManagerString(dpy);

	if (xrm != NULL) {
		xrdb = XrmGetStringDatabase(xrm);

		/* handling colors here without macros to do via loop. */
		int i = 0;
		char loadValue[12] = "";
		for (i = 0; i < 256; i++)
		{
			sprintf(loadValue, "%s%d", "st.color", i);

			if(!XrmGetResource(xrdb, loadValue, loadValue, &type, &ret))
			{
				sprintf(loadValue, "%s%d", "*.color", i);
				if (!XrmGetResource(xrdb, loadValue, loadValue, &type, &ret))
					/* reset if not found (unless in range for defaults). */
					if (i > 15)
						colorname[i] = NULL;
			}

			if (ret.addr != NULL && !strncmp("String", type, 64))
				colorname[i] = ret.addr;
		}

		XRESOURCE_LOAD_STRING("foreground", colorname[defaultfg]);
		XRESOURCE_LOAD_STRING("background", colorname[defaultbg]);
		XRESOURCE_LOAD_STRING("cursorfg", colorname[defaultcs])
		else {
		  // this looks confusing because we are chaining off of the if
		  // in the macro. probably we should be wrapping everything blocks
		  // so this isn't possible...
		  defaultcs = defaultfg;
		}
		XRESOURCE_LOAD_STRING("cursorbg", colorname[defaultrcs])
		else {
		  // see above.
		  defaultrcs = defaultbg;
		}

		XRESOURCE_LOAD_STRING("font", font);
		XRESOURCE_LOAD_STRING("termname", termname);

		XRESOURCE_LOAD_INTEGER("blinktimeout", blinktimeout);
		XRESOURCE_LOAD_INTEGER("bellvolume", bellvolume);
		XRESOURCE_LOAD_INTEGER("borderpx", borderpx);
		XRESOURCE_LOAD_INTEGER("cursorshape", cursorshape);

		XRESOURCE_LOAD_FLOAT("cwscale", cwscale);
		XRESOURCE_LOAD_FLOAT("chscale", chscale);
	}
	XFlush(dpy);
}

void
reload(int sig)
{
	xrdb_load();

	/* colors, fonts */
	xloadcols();
	xunloadfonts();
	xloadfonts(font, 0);

	/* pretend the window just got resized */
	cresize(win.w, win.h);
	redraw();
	/* triggers re-render if we're visible. */
	ttywrite("\033[O", 3, 1);

	signal(SIGUSR1, reload);
}
