#include "config.h"
namespace jaw3d {

namespace tools {

	///////////////////////////////////////// fps_tracker

	fps_tracker::fps_tracker( unsigned int samples ) {
		samples = samples;
		index = 0;
		dtimes = new float[samples];
		full = false;
	}

	fps_tracker::~fps_tracker() {
		delete [] dtimes;
	}

	void fps_tracker::supply( float dtime ) {
		dtimes[index++] = dtime;
		if( index >= samples ) {
			index = 0;
			full = true;
		}
	}

	float fps_tracker::average() {
		unsigned int len = ( full ) ? samples : index;
		float total = 0;
		for( unsigned int i = 0; i < len; i++ ) total += dtimes[i];
		total /= len;
		return total;
	}

} //tools

} //jaw3d
