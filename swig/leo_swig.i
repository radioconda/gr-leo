/* -*- c++ -*- */

#define LEO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "leo_swig_doc.i"

%nodefaultctor gr::leo::generic_noise;
%template(generic_noise_sptr) boost::shared_ptr<gr::leo::generic_noise>;

%nodefaultctor gr::leo::generic_antenna;
%template(generic_antenna_sptr) boost::shared_ptr<gr::leo::generic_antenna>;

%nodefaultctor gr::leo::satellite;
%template(satellite_sptr) boost::shared_ptr<gr::leo::satellite>;

%template(tracker_sptr) boost::shared_ptr<gr::leo::tracker>;

%nodefaultctor gr::leo::generic_attenuation;
%template(generic_attenuation_sptr) boost::shared_ptr<gr::leo::generic_attenuation>;

%nodefaultctor gr::leo::generic_model;
%template(generic_model_sptr) boost::shared_ptr<gr::leo::generic_model>;



%{
#include "leo/generic_noise.h"
#include "leo/generic_antenna.h"
#include "leo/white_gaussian_noise.h"
#include "leo/yagi_antenna.h"
//#include "leo/helix_antenna.h"
//#include "leo/parabolic_reflector_antenna.h"
//#include "leo/custom_antenna.h"
//#include "leo/monopole_antenna.h"
//#include "leo/dipole_antenna.h"
//#include "leo/quadrifilar_helix_antenna.h"
#include "leo/satellite.h"
#include "leo/tracker.h"
#include "leo/generic_attenuation.h"
#include "leo/free_space_path_loss.h"
#include "leo/atmospheric_gases_itu.h"
#include "leo/antenna_pointing_loss.h"
#include "leo/generic_model.h"
#include "leo/leo_model.h"
#include "leo/channel_model.h"
%}

%include "leo/generic_noise.h"
%include "leo/generic_antenna.h"
%include "leo/white_gaussian_noise.h"
//%include "leo/yagi_antenna.h"
//%include "leo/helix_antenna.h"
//%include "leo/parabolic_reflector_antenna.h"
//%include "leo/custom_antenna.h"
//%include "leo/monopole_antenna.h"
//%include "leo/dipole_antenna.h"
//%include "leo/quadrifilar_helix_antenna.h"
%include "leo/satellite.h"
%include "leo/tracker.h"
%include "leo/generic_attenuation.h"
%include "leo/free_space_path_loss.h"
%include "leo/atmospheric_gases_itu.h"
%include "leo/antenna_pointing_loss.h"
%include "leo/generic_model.h"
%include "leo/leo_model.h"
%include "leo/channel_model.h"

GR_SWIG_BLOCK_MAGIC2(leo, channel_model);


