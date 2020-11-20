<p align="center">
    <img src="https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/gltut.png" \>
</p>

***
<p align="center">
    <img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat">
     <img src="https://img.shields.io/badge/first--timers--only-friendly-blue.svg">
     <img src="https://travis-ci.org/freeCodeCamp/how-to-contribute-to-open-source.svg?branch=master">
</p>




# gltut-C 
#### OpenGL Tutorials on C

These tutorials are for the batch 2015-2017 of RKMVERI, OpenGL course (written in C). Please read [LICENSE](LICENSE) for more details.


## Installation

Installation requirements (Debian system aka GNU/Linux, valid at least upto 2016-2020): 
autotools, libglew, libglfw3, libfreetype2, libpng, libm

Libtool is mostly needed to show how a small library libcommon.a can be created, though strictly 
it is not necessary.


```
$ apt-get install autoconf automake libtool libglew-dev libglfw3-dev libfreetype-dev
$ bash ./autogen.sh
$ ./configure
$ make
$ cd src
```


## Examples

#### Tutorial 0 - OpenGL initialization, single buffer

```
$ ./tut0
```

![Tutorial 0](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut0.png)



#### Tutorial 1 - Simple OpenFL operations, multiple buffers

```
$ ./tut1
```

![Tutorial 1](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut1.png)


#### Tutorial 2 - Transformations

```

$ ./tut2
```

![Tutorial 2](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut2.png)


#### Tutorial 3 - Textures

```
$ ./tut3
```

![Tutorial 3](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut3.png)


#### Tutorial 4 - Lighting on flat surfaces

```
$ ./tut4
```

![Tutorial 4](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut4.png)

#### Tutorial 5 - Lighting on curved surfaces

```
$ ./tut5
```
![Tutorial 5](https://raw.githubusercontent.com/wiki/sarvottamananda/gltut-c/img/tut5.png)

***

<details>
<summary>
<a class="btnfire small stroke"><em class="fas fa-chevron-circle-down"></em>&nbsp;&nbsp;Frequently Asked Questions</a>    
</summary>

<ul>
<li>

[ChangeLog](ChangeLog.md)
</li>
<li>

[CODE_OF_CONDUCT](CODE_OF_CONDUCT.md)
</li>
<li>

[COPYING](COPYING)
</li>
<li>

[LICENSE](LICENSE)
</li>



</ul>
</details>




