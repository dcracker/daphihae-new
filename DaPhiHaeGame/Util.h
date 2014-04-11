#define foreach( type, element, list )	\
for ( std::vector<type>::iterator it = list.begin(); it != list.end(); ++it )

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
};