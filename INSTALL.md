# Installation Instructions 


Installation requirements (Debian system aka GNU/Linux, valid at least upto 2016-2020): 
autotools, libglew, libglfw3, libfreetype2, libpng, libm

Libtool is mostly needed to show how a small library libcommon.a can be created, though strictly 
it is not necessary.

TL;DR

```
$ apt-get install autoconf automake libtool libglew-dev libglfw3-dev libfreetype-dev
$ bash ./autogen.sh
$ ./configure
$ make
$ cd src
```

