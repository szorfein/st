# st
Terminal st customized (suckless)

## Patches
+ live-reload from [Xst](https://github.com/gnotclub/xst)
+ [font2](https://st.suckless.org/patches/font2/)

## Commands
Use the `live-reload`:

    xrdb merge ~/.Xresources && kill -USR1 $(pidof st)
