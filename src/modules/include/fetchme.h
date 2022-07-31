#ifndef FETCHME_H
#define FETCHME_H
int cpu_info(void);
int disk(void);
int distro(void);
int gpu_info(void);
int kernel(void);
int memory_info(void);
int package_count(void);
int refresh_rate(void);
int resolution(void);
int shell(void);
int terminal(char* const* envp);
int uptime_info(void);
int username_at_hostname(void);
int wm(void);
#endif
