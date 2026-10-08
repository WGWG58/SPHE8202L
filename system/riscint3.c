#include "config.h"
#include "global.h"
#include "regmap.h"
#include "func.h"
#include "util.h"

#ifdef STB_2_0
int	iIntCnt=0;
void	intr_risc3()
{	
	iIntCnt++;
}
#else
void	intr_risc3()
{	

}
#endif



