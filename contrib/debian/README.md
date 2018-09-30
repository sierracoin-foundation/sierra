Debian
======

This directory contains files used to package sierrad/sierra-qt
for Debian-based Linux systems. If you compile sierrad/sierra-qt yourself, there are some useful files here.

## sierra: URI support ##

sierra-qt.desktop (Gnome / Open Desktop)

To install:

	sudo desktop-file-install sierra-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sierra-qt binary to `/usr/bin`
and the `../../share/pixmaps/sierra128.png` to `/usr/share/pixmaps`

sierra-qt.protocol (KDE)