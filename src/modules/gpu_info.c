#include "./include/fetchme.h"
int
gpu_info(const char *color_distro)
{
#if GPU_INFO == 2
	gpu_info_v2(color_distro);
#elif GPU_INFO == 1
	gpu_info_v1(color_distro);
#else
	;
#endif
	return 0;
}
