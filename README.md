# st
Terminal st customized (suckless)

## Patches
+ [anygeometry](https://st.suckless.org/patches/anygeometry/)
+ [boxdraw](https://st.suckless.org/patches/boxdraw/)
+ [desktopentry](https://st.suckless.org/patches/desktopentry/)
+ [font2](https://st.suckless.org/patches/font2/)
+ [ligatures](https://st.suckless.org/patches/ligatures/)
+ live-reload from [Xst](https://github.com/gnotclub/xst)
+ [scrollback](https://st.suckless.org/patches/scrollback/)

## Commands
Use the `live-reload`:

    xrdb merge ~/.Xresources && kill -USR1 $(pidof st)

## Dependencies

    Xlib, harfbuzz, xrdb

## Install

    make clean install
