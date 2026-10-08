#include "user_init.h"
#include "pu8560.h"
#include "config.h"
#include "regmap.h"
#include "global.h"

#include "epp.h"
#include "gpio.h"

#ifdef SUPPORT_CARD_STORAGE
#include "cardfs.h"
#endif

//#define     GPIO_DBG        1

#ifdef IC_1002
#include "gpio_1002.c"
#elif defined(IC_8202L)
#include "gpio_8202L.c"
#elif defined(IC_8203A)
#include "gpio_8203A.c"
#else
#include "gpio_8202.c"
#endif


