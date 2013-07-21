#ifndef __UTILS_H__
#define __UTILS_H__

///////////////////////////////////////////////// manager

template< class T > struct manager {
	unsigned int load( T newItem ) {
		items.push_back( newItem );
		return items.size()-1;
	}
	T get( unsigned int i ) { return items[i]; }
	vector< T > items;
};

///////////////////////////////////////////////// timer

namespace TIMER {

	static chrono::high_resolution_clock::time_point time_for_diff = chrono::high_resolution_clock::now();
	static float last_diff;

	static inline float nanoseconds() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		float time_span = float(chrono::duration_cast< chrono::duration< float > >( t.time_since_epoch() ).count() );
		return time_span;
	}

	static inline float diff() {
		chrono::high_resolution_clock::time_point t = chrono::high_resolution_clock::now();
		last_diff = float(chrono::duration_cast< chrono::duration< float > >( t-time_for_diff ).count() );
		time_for_diff = t;
		return last_diff;
	}

	static inline unsigned int fps() {
		if( last_diff == 0 ) return 0;
		return (unsigned int)1.0f/last_diff;
	}

}

#endif //__UTILS_H__
