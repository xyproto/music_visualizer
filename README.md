# Music Visualizer

Visualize music and audio. Compiles on Arch Linux using [cxx](https://github.com/xyproto/cxx).

The idea is that this can be used on a Raspberry Pi in combination with a projector to light up the performer to the beats of the music.

![Screenshot](img/muviz_screenshot.jpg)

I have not tested it on a Raspberry Pi yet, but that is the plan.

## Fork information

This is a fork of [bradleybauer/music_visualizer](https://github.com/bradleybauer/music_visualizer) (GPL3 licensed).

The default visualizer in `muviz` is based on one of the visualizers from `music_visualizer` and also a [shader that I wrote](https://www.shadertoy.com/view/3slSRN).

It also contains files from:

* A fork of [bradleybauer/SimpleFileWatcher](https://github.com/bradleybauer/SimpleFileWatcher)
* Which is a fork of [shadowndacorner/SimpleFileWatcher](https://github.com/shadowndacorner/SimpleFileWatcher)
* Which is a fork of [apetrone/simplefilewatcher](https://github.com/apetrone/simplefilewatcher)

SimpleFileWatcher is MIT licensed.

## Build instructions

    cxx

## Installation instructions

Set `$pkgdir` to the root of where you want muviz to be installed.

    DESTDIR="$pkgdir" PREFIX=/usr cxx install

## Package instructions

    cxx pkg

## Dependencies

    ffts glfw libpulse rapidjson

## Installation on Arch Linux

Just install `muviz` from AUR using your favorite AUR helper.

## General information

* Version: 1.1.1
* License: MIT and GPL3. See the [`LICENCE`](LICENSE) file for more information.
