AC_PREREQ(2.63.2)

AC_INIT([Phosphorus], 0.2, [hjdskes@gmail.com], [phosphorus], [https://unia.github.io/phosphorus])

# Dependencies
GTK_REQUIRED=3.12.0
GDKPIXBUF_REQUIRED=2.4.0
LIBPEAS_REQUIRED=1.0.0
PYGOBJECT_REQUIRED=3.0.0

AC_SUBST(PHOSPHORUS_API_VERSION, 1.0)

AC_CONFIG_HEADERS(config.h)
AC_DEFINE_UNQUOTED(UNUSED, [__attribute__ ((unused))], [Wrapper over __attribue__ ((unused))])

AM_INIT_AUTOMAKE([1.11 foreign dist-xz no-dist-gzip subdir-objects -Wno-portability])
AM_SILENT_RULES(yes)

# Check for programs
AC_PROG_CC
AC_PROG_CC_STDC

# Initialize libtool
LT_PREREQ(2.2.6)
LT_INIT(disable-static)

# Resources
AC_PATH_PROG(GLIB_COMPILE_RESOURCES, glib-compile-resources)

# Internationalization
IT_PROG_INTLTOOL(0.50.1)
AM_GLIB_GNU_GETTEXT

AC_SUBST(GETTEXT_PACKAGE, AC_PACKAGE_NAME)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Gettext package.])

# GSettings
GLIB_GSETTINGS

# Plugins
AM_PATH_PYTHON(3.2.3)
GOBJECT_INTROSPECTION_CHECK(0.9.3)

AC_SUBST(PHOSPHORUS_PLUGINS_DATA_DIR, "$datadir/phosphorus/plugins")
AC_SUBST(PHOSPHORUS_PLUGINS_LIBS_DIR, "$libdir/phosphorus/plugins")

# Active plugins for the gschema
ACTIVE_PLUGINS=

AC_DEFUN([APPEND], [
	if test "$ACTIVE_PLUGINS" = ""; then
		ACTIVE_PLUGINS="$1"
	else
		ACTIVE_PLUGINS="${ACTIVE_PLUGINS}, $1"
	fi])

# Check for GNOME support
AC_ARG_ENABLE([gnome],
              AS_HELP_STRING([--enable-gnome[=@<:@no/yes@:>@]],[Build with GNOME Shell support]),
              [enable_gnome=$enableval],
              [enable_gnome="yes"])
if test "$enable_gnome" = "yes"; then
	APPEND('GnomeWallpaperSetter')
fi
AM_CONDITIONAL(ENABLE_GNOME, test "$enable_gnome" = "yes")

# Check for XLib support
AC_ARG_ENABLE([xlib],
              AS_HELP_STRING([--enable-xlib[=@<:@no/yes@:>@]],[Build with XLib support]),
              [enable_xlib=$enableval],
              [enable_xlib="yes"])
if test "$enable_xlib" = "yes"; then
	PKG_CHECK_MODULES([XLIB_PLUGIN], [x11
					  gdk-pixbuf-xlib-2.0])
	APPEND('XLibWallpaperSetter')
fi
AM_CONDITIONAL(ENABLE_XLIB, test "$enable_xlib" = "yes")

AC_SUBST(ACTIVE_PLUGINS)

# Package requirements
PKG_CHECK_MODULES([PHOSPHORUS_BASE], [gtk+-3.0 >= GTK_REQUIRED,
				      gdk-pixbuf-2.0 >= GDKPIXBUF_REQUIRED])
PKG_CHECK_MODULES([PHOSPHORUS_PLUGIN], [libpeas-1.0 >= LIBPEAS_REQUIRED
					libpeas-gtk-1.0 >= LIBPEAS_REQUIRED
					pygobject-3.0 >= PYGOBJECT_REQUIRED])

AC_CONFIG_FILES(Makefile
		data/Makefile
		data/org.unia.phosphorus.gschema.xml
		data/phosphorus.desktop.in
		data/phosphorus.pc
		data/phosphorus-plugin.pc
		plugins/Makefile
		po/Makefile.in
		src/Makefile)

AC_OUTPUT

AC_MSG_RESULT([
        $PACKAGE $VERSION
        ========

        prefix:                 ${prefix}
        libdir:                 ${libdir}
        sysconfdir:             ${sysconfdir}
        exec_prefix:            ${exec_prefix}
        bindir:                 ${bindir}
        datarootdir:            ${datarootdir}

        compiler:               ${CC}
        cflags:                 ${CFLAGS}
        ldflags:                ${LDFLAGS}

        GNOME Shell plugin:     ${enable_gnome}
        XLib plugin:            ${enable_xlib}
])

