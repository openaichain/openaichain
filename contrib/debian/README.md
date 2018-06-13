
Debian
====================
This directory contains files used to package oaccoind/oaccoin-qt
for Debian-based Linux systems. If you compile oaccoind/oaccoin-qt yourself, there are some useful files here.

## oaccoin: URI support ##


oaccoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install oaccoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your oaccoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/oaccoin128.png` to `/usr/share/pixmaps`

oaccoin-qt.protocol (KDE)

