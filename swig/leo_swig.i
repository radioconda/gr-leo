/* -*- c++ -*- */

#define LEO_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "leo_swig_doc.i"

%{
#include "leo/leo_channel_model.h"
#include "leo/sat_tracker.h"
%}


%include "leo/leo_channel_model.h"
GR_SWIG_BLOCK_MAGIC2(leo, leo_channel_model);
%include "leo/sat_tracker.h"
