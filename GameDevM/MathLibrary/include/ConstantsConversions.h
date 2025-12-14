#ifndef CONTSTANTSCONVERSIONS_H
#define CONTSTANTSCONVERSIONS_H
    /// This is used in normalizing vectors. Dividing by zero is a well known
	/// problem but dividing by nearly zero is also a problem. 1.0x10-7 is very
	/// small in "float" percision (IEEE 754). 

#ifndef VERY_SMALL
#define VERY_SMALL 1.0e-7f
#endif

#ifndef VERY_CLOSE_TO_ONE 
#define	VERY_CLOSE_TO_ONE 0.9999f
#endif

#ifndef FLOAT_PI
#define FLOAT_PI 3.141592f
#endif

#ifndef DEGREES_TO_RADIANS
#define DEGREES_TO_RADIANS (FLOAT_PI / 180.0f)
#endif	

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES (180.0f / FLOAT_PI)
#endif


#endif