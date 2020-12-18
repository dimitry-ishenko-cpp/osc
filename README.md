# osc++: OSC Library for C++

The osc++ library allows one to create and parse [OSC (Open Sound Control)](http://opensoundcontrol.org/spec-1_0) packets.

## Installation

### Binary

Debian/Ubuntu/etc:

```console
$ ver=0.5
$ url=https://github.com/dimitry-ishenko-casparcg/osc/releases/download/v${ver}
$ wget ${url}/libosc++_${ver}_amd64.deb
$ sudo apt install ./libosc++_${ver}_amd64.deb
```

Install the development package, if you are planning to develop applications with `osc++`:
```console
$ wget ${url}/libosc++-dev_${ver}_amd64.deb
$ sudo apt install ./libosc++-dev_${ver}_amd64.deb
```

RaspberryPi:

```console
$ ver=0.5
$ url=https://github.com/dimitry-ishenko-casparcg/osc/releases/download/v${ver}
$ wget ${url}/libosc++_${ver}_armhf.deb
$ sudo apt install ./libosc++_${ver}_armhf.deb
```

Install the development package, if you are planning to develop applications with `osc++`:
```console
$ wget ${url}/libosc++-dev_${ver}_armhf.deb
$ sudo apt install ./libosc++-dev_${ver}_armhf.deb
```

### From source

Stable version (requires [CMake](https://cmake.org/) >= 3.1):

```console
$ ver=0.5
$ wget https://github.com/dimitry-ishenko-casparcg/osc/archive/v${ver}.tar.gz
$ tar xzf v${ver}.tar.gz
$ mkdir osc-${ver}/build
$ cd osc-${ver}/build
$ cmake ..
$ make
$ sudo make install
```

Latest master (requires [git](https://git-scm.com/) and [CMake](https://cmake.org/) >= 3.1):

```console
$ git clone https://github.com/dimitry-ishenko-casparcg/osc.git
$ mkdir osc/build
$ cd osc/build
$ cmake ..
$ make
$ sudo make install
```

## Developing with osc++

Usage examples:
```cpp
```

## Authors

* **Dimitry Ishenko** - dimitry (dot) ishenko (at) (gee) mail (dot) com

## License

This project is distributed under the GNU GPL license. See the
[LICENSE.md](LICENSE.md) file for details.
