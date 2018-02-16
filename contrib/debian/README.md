
Debian
====================
This directory contains files used to package ethfd/ethf-qt
for Debian-based Linux systems. If you compile ethfd/ethf-qt yourself, there are some useful files here.

## ethf: URI support ##


ethf-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install ethf-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your ethfqt binary to `/usr/bin`
and the `../../share/pixmaps/ethf128.png` to `/usr/share/pixmaps`

ethf-qt.protocol (KDE)

