# st
Terminal st customized (suckless)

## Patches
+ [desktopentry](https://st.suckless.org/patches/desktopentry/)
+ [font2](https://st.suckless.org/patches/font2/)
+ [ligatures](https://st.suckless.org/patches/ligatures/)
+ live-reload from [Xst](https://github.com/gnotclub/xst)

## Commands
Use the `live-reload`:

    xrdb merge ~/.Xresources && kill -USR1 $(pidof st)
