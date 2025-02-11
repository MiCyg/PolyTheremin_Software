#ifndef __FIXFLOAT__
#define __FIXFLOAT__

#include "comlib.h"

typedef int32_t fix32_t;

#define int2fix32(a) ((fix32_t)(a << 15))
#define fix2int32(a) ((int32_t)(a >> 15))

#define float2fix32(a) (fix32_t)(a * 32768)
#define fix322float(a) ((double)(a) / 32768)

#define sqrtfix(a) (float2fix(sqrt(fix2float(a))))

// opeerations
#define multfix32(a,b) ((fix32_t)((((int64_t)(a))*((int64_t)(b)))>>15))
#define divfix32(a,b) ((fix32_t)((((int64_t)(a)<<15)/(b)))) 





#endif // __FIXFLOAT__