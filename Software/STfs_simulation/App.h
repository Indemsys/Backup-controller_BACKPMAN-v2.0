#include <stdint.h>
#include <string.h>

#define         STFS_SIMULATOR_FLASH_DRIVER

#define         LOG_STR_MAX_SZ 1024

void            LOGs(const char *name, unsigned int line_num, const char *fmt_ptr, ...);

#define         APPLOG(...)    LOGs(__FUNCTION__, __LINE__, ##__VA_ARGS__);


typedef struct
{
    uint32_t cycles;
    uint32_t ticks;

} T_sys_timestump;

#define  Hw_timestump_diff64_us(...)     0
#define  Get_hw_timestump(...)

extern void*    App_malloc(uint32_t size);
extern void     App_free(void *block_ptr);

