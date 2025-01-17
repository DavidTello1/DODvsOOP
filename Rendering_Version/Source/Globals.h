#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

// Disable STL exceptions
#ifndef _HAS_EXCEPTIONS
#define _HAS_EXCEPTIONS 0
#endif
#define _STATIC_CPPLIB

/* CHARS AT END INDICATES THE TYPE OF LOG TO ENABLE FILTERS
* Characters must be written as string type %s
* v - verbose
* g - geometry
* d - debug
* e - error
* w - warning //TODO
* Ex: LOG("My log string: %s, my number: %d","My string", 23,'v')
*/
#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)
#define MIN(a,b) ((a)<(b)) ? (a) : (b)
#define MAX(a,b) ((a)>(b)) ? (a) : (b)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.14159265358979323846f
#define TWO_PI 6.28318530717958647692f
#define HALF_PI 1.57079632679489661923f
#define QUARTER_PI 0.78539816339744830961f
#define INV_PI 0.31830988618379067154f
#define INV_TWO_PI 0.15915494309189533576f
#define HAVE_M_PI

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned long long int u64;
typedef unsigned long long UID;


// Align 16, use if you have math elements in your class like float4x4 or AABB
#define ALIGN_CLASS_TO_16 \
	void* operator new(size_t i) { return _aligned_malloc(i,16); }\
    void operator delete(void* p) { _aligned_free(p); }

#define ARRAY_COUNT(array) (sizeof(array)/sizeof(array[0]))

// Deletes a buffer
#define RELEASE( x )\
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x )\
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Colors
#define RED     { 1.0f, 0.0f, 0.0f , 1.0f}
#define GREEN   { 0.0f, 1.0f, 0.0f , 1.0f}
#define BLUE    { 0.0f, 0.0f, 1.0f , 1.0f}
#define YELLOW  { 1.0f, 1.0f, 0.0f , 1.0f}

// ECS
const int MAX_ENTITIES = 10000;
const int MAX_COMPONENTS = 32;

typedef unsigned int EntityIdx;
