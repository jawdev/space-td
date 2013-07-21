#ifndef __UTILS_H__
#define __UTILS_H__
namespace jaw3d {

///////////////////////////////////////////////// tools

 /* Useful functions */
namespace tools {
	
	 /* read file and return char* */
	inline char* file_get_contents( const char* filename, bool zero_term=false ) {
		ifstream in( filename, ios::in|ios::binary );
		if( !in ) {
			cerr << "tools::file_get_contents> File could not be read: " << filename << endl;
			exit( 1 );
		}
		char *contents;
		in.seekg( 0, ios::end );
		unsigned int len = (unsigned int)in.tellg();
		contents = new char[len+1];
		in.seekg( 0, ios::beg );
		in.read( contents, len );
		in.close();
		contents[len] = 0;
		return contents;
	}
}

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

namespace timer {

	static chrono::high_resolution_clock::time_point time_for_diff = chrono::high_resolution_clock::now();
	static float last_diff;

	static inline float time_since_epoch() {
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

}
#endif //__UTILS_H__
