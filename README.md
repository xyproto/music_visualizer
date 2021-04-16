# Music Visualizer

Visualize music and audio. Tested on Arch Linux under both X and Wayland.

The idea is that this can be used on a Raspberry Pi in combination with an old projector to light up the performer to the beats of the music. I have not tested it on a Raspberry Pi yet, but this is the plan.

The default visualizer in `muviz` is based on both one of the visualizers from `music_visualizer` and also a [shader that I wrote](https://www.shadertoy.com/view/3slSRN).

Screenshot of the default music visualizer:

![Screenshot](img/muviz_screenshot.jpg)

## Fork information

This is a fork of [bradleybauer/music_visualizer](https://github.com/bradleybauer/music_visualizer) (GPL3 licensed).

It also contains files from:

* A fork of [bradleybauer/SimpleFileWatcher](https://github.com/bradleybauer/SimpleFileWatcher)
* Which is a fork of [shadowndacorner/SimpleFileWatcher](https://github.com/shadowndacorner/SimpleFileWatcher)
* Which is a fork of [apetrone/simplefilewatcher](https://github.com/apetrone/simplefilewatcher)

SimpleFileWatcher is MIT licensed.

## Command line options

Use `--help` or `--version` to display help or the current version. Use `-l` to list the available music visualizer. Supply one of the names as the first argument to `muviz` to use them.

## Build instructions

`muviz` can be built with [cxx](https://github.com/xyproto/cxx). Simply run:

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
