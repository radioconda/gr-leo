# gr-leo: GNU Radio space telecommunication simulator

A GNU Radio Out-of-Tree module that simulates the telecommunication channel between orbiting satellites and Ground Stations.

## Requirements
* GNU Radio ( > 3.7.7 )
* CMake ( > 2.6)
* G++ (with C++11 support)
* VOLK
* [C++ SGP4 Satellite Library](https://github.com/dnwrnr/sgp4) (will be automatically installed if not present)

## Installation

1. `git clone https://gitlab.com/librespacefoundation/gr-leo`
2. `cd gr-leo`
3. `mkdir build & cd build`
4. `cmake ..`
5. `make`
6. `sudo make install`

If this is the first time you are building the gr-leo module run
`sudo ldconfig`

### Advanced
By default, the **gr-leo** module will use the default installation prefix.
This highly depends on the Linux distribution. You can use the `CMAKE_INSTALL_PREFIX`
variable to alter the default installation path.
E.g:

`cmake -DCMAKE_INSTALL_PREFIX=/usr ..`

Another common control option is the library sugffix of the Linux distribution.
There are distributions like Fedora, openSUSE, e.t.c that the their 64-bit version
use the `lib64` folder to store the 64-bit versions of their dynamic libraries.
On the other hand, distributions like Ubuntu do the exact opposite. They use
`lib` directory for the libraries of the native architecture and place the 32-bit versions
on the `lib32` directory. In any case the correct library directory suffix
can be specified with the `LIB_SUFFIX` variable. For example:

`cmake -DLIB_SUFFIX=64 -DCMAKE_INSTALL_PREFIX=/usr -DINCLUDE_DEBUG_BLOCKS=OFF ..`

will install the libraries at the `/usr/lib64` directory.

## SDRMakerspace
**gr-leo** module is implemented in the scope of [SDR Makerspace](https://sdrmaker.space/), an initiative of the [European Space Agency](https://esa.int) and [Libre Space Foundation](https://libre.space). 

## License
&copy; 2018 [Libre Space Foundation](http://librespacefoundation.org).

Licensed under the [GPLv3](LICENSE).
