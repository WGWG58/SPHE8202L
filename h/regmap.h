#ifndef __REGMAP_DVD_H
#define __REGMAP_DVD_H

#if defined(IC_1002)
#include "regmap_1002.h"
#elif defined(IC_8202L)
#include "regmap_8202L.h"
#elif  defined(IC_8203A)
#include "regmap_8203A.h"
#elif  defined(SPHE8202)
#include "regmap_8202.h"
#elif	defined(SPHE1000)
#include "regmap_1000.h"
#else
#include "regmap_8200.h"
#endif

#endif/*__REGMAP_DVD_H*/

