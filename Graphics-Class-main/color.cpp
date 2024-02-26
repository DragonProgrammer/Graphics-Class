#include "color.h"
#include <iostream>
using std::ostream;

ostream& operator << (ostream &os, const color &s) {
	    return (os << "red: " << s.r << " green: " << s.g << " blue: " << s.b );
}


