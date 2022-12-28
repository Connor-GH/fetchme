#include "./include/fetchme.h"
int
gpu_info(void)
{
#if GPU_INFO == 2
	gpu_info_v2();
#else
	gpu_info_v1();
#endif
	return 0;
}
