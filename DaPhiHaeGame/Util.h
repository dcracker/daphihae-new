#ifndef Util_H_
#define Util_H_

#define foreach( type, it, list )	\
for ( std::vector<type>::iterator it = list.begin(); it != list.end(); ++it )
#define foreach_const( type, it, list )	\
for ( std::vector<type>::const_iterator it = list.begin(); it != list.end(); ++it )

class Util {
public:
	template<typename T>
	static T Clamp( T value, T minBound, T maxBound ) {
		if ( value < minBound ) {
			value = minBound;
		}
		else if ( value > maxBound ) {
			value = maxBound;
		}

		return value;
	}

	template <typename T>
	static void FreePointerArray( std::vector<T>& container ) {
		for ( typename std::vector<T>::iterator it = container.begin(); it != container.end(); ++it ) {
			delete *it;
		}
		container.clear();
	}
};

#endif	// Util_H_
