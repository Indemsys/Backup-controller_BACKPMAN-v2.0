#include "App.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


extern void Write_to_mem(const char *name, unsigned int line_num, char *str);

/*-----------------------------------------------------------------------------------------------------


  \param name
  \param line_num
  \param fmt_ptr
-----------------------------------------------------------------------------------------------------*/
void  LOGs(const char *name, unsigned int line_num, const char *fmt_ptr, ...)
{
  char str[LOG_STR_MAX_SZ];
  va_list ap;

  va_start(ap, fmt_ptr);
  vsnprintf(str, LOG_STR_MAX_SZ - 1, (char *) fmt_ptr, ap);
  va_end(ap);
  Write_to_mem(name, line_num, str);
}

/*-----------------------------------------------------------------------------------------------------


  \param size

  \return void*
-----------------------------------------------------------------------------------------------------*/
void*  App_malloc(uint32_t size)
{
  return malloc(size);
}

/*-----------------------------------------------------------------------------------------------------


  \param block_ptr
-----------------------------------------------------------------------------------------------------*/
void  App_free(void *block_ptr)
{
  free(block_ptr);
}
