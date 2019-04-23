## gr-leo: A GNU Radio space telecommunication simulator

Gr-leo is a GNU Radio Out-of-Tree module [1] that simulates the telecommunication channel between orbiting satellites and Ground Stations.

## Introduction
Telecommunication systems are affected by a plethora of impairments imposed from the wireless channel. The development, debugging and evaluation of such systems should be performed under realistic channel conditions, that are difficult to be simulated on the lab. This prerequisite becomes even more crucial in the case of satellite missions. GNU Radio provides a variety of channel estimation blocks that however cannot be used efficiently for the purposes of a space telecommunication channel.

Gr-leo aspires to fill this gap with the implementation of a GNU Radio module that simulates the operation of an Earth-Satellite system and a variety of impairments that my occur during the space channel communication. For example, frequency shift due to the Doppler effect, the variable path loss due to the satellite's trajectory or the atmospheric effects along the path are proven to pose significant degradation on the communication channel. 

## System Architecture

The gr-leo module is written in C++ and follows the block-programming notion of GNU Radio. 
More specifically, it divides its implementation into different processing blocks that simulate each one of the different components of the space channel communication system. These blocks, that are also available through the GNU Radio Companion, can be combined appropriately with the existing built-in processing blocks of GNU Radio. The architecture of the gr-leo module is presented graphically in Figure 1. Below, there is a description of the blocks provided by gr-leo.

### Channel model block
The channel model block is implemented as a GNU Radio synchronous block and accepts as a parameter a [channel model definition](#channel-model-definition). The main task of this block is to appropriately pass the signal from its input port to the worker function of the channel model definition, alongside with a pointer to its output buffer, for as long as the satellite observation lasts. In addition, there is the possibility to tune the noise-floor of the communication channel by adding white Gaussian noise of predefined power.
Finally, an optional message port that outputs logging information in CSV format exists.
 
![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/1a56931066a48dee02861cdbdcc10b93/image.png)

Fig 2. A GRC flowgraph that contains the channel model block.


### Channel model definition
Channel model definitions are the heart of gr-leo, as they link the different components that constitute the Earth-space communication system in a single GNU Radio variable block. More specifically, a channel model block accepts a list of required parameters, such as the Earth ground station [tracker](#tracker), an option that defines the transmission mode (downlink or uplink) and a series of other options that describe the specific [impairments](#impairments) that will be taken into account at the channel simulation.

As regards to the implementation, every model definition block is described by a C++ class that extends the generic_model parent class and must implement the pure virtual generic_work function. The generic_work function is called by the [channel model block](#channel-model-block), appropriately manipulates the input signal and writes the resulting signal to the output buffer. 

![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/8930f9eeee062a08284e7676eeb5834c/image.png)
Fig 3. Α GRC block example of model definition for the LEO channel.

### Tracker
The Earth-based ground station is represented in gr-leo, as an instance of the Tracker class. It holds parameters for all the required information to fully describe a ground station tracking an orbiting satellite, such as:
*  the [satellite](#satellite) object of interest
*  the ground station's coordinates (Latitude, Longitude and Altitude)
*  the operating TX/RX frequencies
*  the TX/RX [antenna](#antenna) objects
*  the observation timeframe in ISO-8601 UTC format
*  the observation time resolution in us

Moreover, the Tracker class is responsible to appropriately call the API of C++ SGP4 [2] for Two-Line-Element (TLE) [3] parsing and every calculation that is required to obtain orbit specific information (i.e distance from ground station, velocity etc).

![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/94e41214d5c64756141a3b57c81627b6/image.png)

### Satellite
A satellite is represented in gr-leo, as an instance of the Satellite class. It holds parameters for all the required information to describe an orbiting satellite, such as:
*  the TLE that describes the orbit
*  the satellite's operating TX/RX frequencies
*  the TX/RX [antenna](#antenna) objects

![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/654752189bda656011b1eeec78e8a02a/image.png)

### Antenna
Different types of antennas are taken into consideration by gr-leo, including yagi, helix, quadrifilar helix, monopole, dipole, parabolic reflector and custom. Each one is described by a C++ class that extends the parent generic_antenna and appropriately implements the pure virtual functions get_gain, get_beamwidth, get_rolloff_gain. In addition, each class accepts different parameters and may implement various functions, based on the corresponding type. 

The AMSAT-IARU Link Mοdel spreadsheet [4] is used as a reference for the calculation of the gain, beamwidth and roll-off gain for each of the antenna types.

For use in the GNU Radio companion, the antenna is represented with a GNU Radio variable block, that is instantiated appropriately, based on the value of the "Type" dropdown. An example is show in Fig 6.

![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/9516c52da9961351af773a9d8285a0a7/image.png)

Fig 6. An example of different types of antennas shown in GRC

### Impairments
A transmission from a satellite to a ground station and vice versa may be subject to a variety of impairments. The relative motion of the orbiting satellite, the operating frequencies, the antenna setup of the telecommunication system and the various atmospheric phenomena are factors that significantly affect the performance of the communication. 

In gr-leo, a variety of such impairments is taken into consideration and is included in the simulation of the space telecommunication channel. Knowing the exact position of the satellite on a specific observation timeframe, by taking advantage of the [tracker](#tracker) class, gr-leo calculates each one of the impairments that are described below.

#### Attenuation
Every phenomenon that induces attenuation on a transmission through the space telecommunication channel is described by C++ class, that extends the generic_attenuation parent class. The generic_attenuation class has some static variables that are shared among the derived attenuation classes and hold information about:
*  the operationg frequency of the system
*  the elevation angle of the satellite at a given time instance
*  the distance between the ground station and the satellite at a given time instance

A [channel model definition](#channel-model-definition) declares the appropriate types of attenuation and calculates the total loss by summing up the returned value from the pure virtual method get_attenuation from each one of the derived classes.

##### Free-space path loss
The ITU recommendation P.619-3 [5] describes a formula to calculate the free-space path loss, the most basic form of attenuation assuming the complete radio path is in a vacuum with no obstruction. It depends only on the operating frequency $`f`$ (GHz) and the distance $`d`$ (km) between the Earth ground station and the satellite, according to:

```math
L_{fs} = 92.45 + 20 \ log_{10}(f\cdot d)
```

From the above formula we subtract the receiving and transmitting antenna gains $`G_{R}`$ and $`G_{T}`$.

##### Atmospheric gasses attenuation
Attenuation on the transmitted signal through the Earth-space telecommunication channel is induced by the 
atmospheric gases absorption. Atmospheric absorption depends strongly upon the distribution of molecules along the path between the satellite and the ground station and is nearly insignificant for frequencies below 2 GHz. In gr-leo, this attenuation is implemented following:
*  the method described in the Annex 1 of the ITU recommendation P.676-11 [6]
*  the method described in Radiowave Propagation in Satellite Communications by Louis J. Ippolito Jr [7]

##### Rainfall attenuation
The loss due to precipitation in the transmission path is a major concern associated with the Earth-space communication systems, especially for operating frequencies above 5 GHz. Gr-leo follows the general method described in the ITU recommendation P.618-13 [8] to estimate the amplitude degradation due to heavy rainfall along the path. The method is dependent to :
* the point rainfall rate for the location for 0.01% of an average year $`R_{001}`$ (mm/h)
* the height above mean sea level of the earth station $`h_s`$ (km)
* the satellite elevation angle $`\theta`$ (degrees)
* the latitude of the earth station $`\phi`$ (degrees)
* the operating frequency $`f`$ (GHz)

If there is local data, an option to provide custom value for $`R_{001}`$ is available, otherwise the digital map provided in the ITU recommendation P.837 [9] is used. 

##### Antenna pointing loss

#### Doppler frequency shift
When a satellite orbits the Earth its relative distance from a ground station varies. Due to this variation of the relative distance, the receiver accepts the frequency of radio wave transmitted on the link with an apparent increase or decrease. This phenomenon is called Doppler effect and is dependent to the operating frequency $`f`$ (Hz), the range variation rate $`V_r`$ (m/s) and the speed of light $`c`$ (m/s), according to:

```math
\Delta f_{d} = V_r \cdot f / c 
``` 
where $`\Delta f_d`$ is measured in Hz

## Requirements
* GNU Radio ( > 3.7.7 )
* CMake ( > 2.6)
* G++ (with C++11 support)
* Boost C++ Libraries ( > 1.35.0 )
* VOLK
* SWIG
* [C++ SGP4 Satellite Library](https://github.com/dnwrnr/sgp4) (will be automatically installed if not present)

## Installation

1. `git clone https://gitlab.com/librespacefoundation/gr-leo`
2. `cd gr-leo`
3. `mkdir build && cd build`
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

## Usage
Please mind the example GNU Radio flowgraphs that exist under the /examples directory.

## Documentation

For more information about gr-leo implementation, visit the Doxygen HTML pages [here](https://librespacefoundation.gitlab.io/gr-leo).

## License
**gr-leo** module is implemented in the scope of [SDR Makerspace](https://sdrmaker.space/), an initiative of the [European Space Agency](https://esa.int) and [Libre Space Foundation](https://libre.space). 


&copy; 2018 [Libre Space Foundation](http://librespacefoundation.org) under the [GPLv3](LICENSE).

![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/f7070aff44bc207ce9d722d4076411df/image.png)
![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/5f7039bb07ae840b3a621454c20c549b/image.png)
![image](https://gitlab.com/librespacefoundation/gr-leo/wikis/uploads/f3c8a9172f71c0bfcc22b93969c98497/image.png)

## References
1. ##### [https://wiki.gnuradio.org/index.php/OutOfTreeModules](https://wiki.gnuradio.org/index.php/OutOfTreeModules)
2. ##### [https://www.danrw.com/sgp4/](https://www.danrw.com/sgp4/)
3. ##### [https://en.wikipedia.org/wiki/Two-line_element_set](https://en.wikipedia.org/wiki/Two-line_element_set)
4. ##### [http://www.amsatuk.me.uk/iaru/spreadsheet.htm](http://www.amsatuk.me.uk/iaru/spreadsheet.htm)
5. ##### [https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.619-3-201712-I!!PDF-E.pdf](https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.619-3-201712-I!!PDF-E.pdf)
6. ##### [https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.676-11-201609-I!!PDF-E.pdf](https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.676-11-201609-I!!PDF-E.pdf)
7. ##### [https://books.google.gr/books?id=OiAyBwAAQBAJ&source=gbs_similarbooks](https://books.google.gr/books?id=OiAyBwAAQBAJ&source=gbs_similarbooks)
8. ##### [https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.618-13-201712-I!!PDF-E.pdf](https://www.itu.int/dms_pubrec/itu-r/rec/p/R-REC-P.618-13-201712-I!!PDF-E.pdf)
9. ##### [https://www.itu.int/rec/R-REC-P.837-7-201706-I/en](https://www.itu.int/rec/R-REC-P.837-7-201706-I/en)

