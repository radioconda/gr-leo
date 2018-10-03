/* -*- c++ -*- */

#define LEO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "leo_swig_doc.i"

%nodefaultctor gr::leo::satellite;
%template(satellite_sptr) boost::shared_ptr<gr::leo::satellite>;

%nodefaultctor gr::leo::tracker;
%template(tracker_sptr) boost::shared_ptr<gr::leo::tracker>;

%nodefaultctor gr::leo::generic_model;
%template(generic_model_sptr) boost::shared_ptr<gr::leo::generic_model>;

%nodefaultctor gr::leo::generic_antenna;
%template(generic_antenna_sptr) boost::shared_ptr<gr::leo::generic_antenna>;


%{
#include "leo/satellite.h"
#include "leo/tracker.h"
#include "leo/generic_antenna.h"
#include "leo/yagi_antenna.h"
#include "leo/generic_model.h"
#include "leo/leo_model.h"
#include "leo/channel_model.h"
%}

%include "leo/satellite.h"
%include "leo/tracker.h"
%include "leo/generic_antenna.h"
%include "leo/yagi_antenna.h"
%include "leo/generic_model.h"
%include "leo/leo_model.h"
%include "leo/channel_model.h"

GR_SWIG_BLOCK_MAGIC2(leo, channel_model);


