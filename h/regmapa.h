#include "ver.h"

#if defined(IC_1002)
#include "regmapa_1002.h"
#elif defined(IC_8202L)
#include "regmapa_8202L.h"
#elif	defined(IC_8203A)
#include "regmapa_8203A.h"
#elif	defined(SPHE8202)
#include "regmapa_8202.h"
#elif	defined(SPHE1000)
#include "regmapa_1000.h"
#else //!SPHE8202
#include "regmapa_8200.h"
#endif //!SPHE8202
