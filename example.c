#include <ezcmd.h>
#include <stdio.h>
#include <stdlib.h>

char g_cmdbuf[0xff];

/* Simple implementation. Just get a char */

char ezcmd_getc()
{
  return getchar();
}

int main(void)
{
  /* Get full command + arguments */

  struct ezcommand cmd;
  ezcmd_start(&cmd, g_cmdbuf, sizeof(g_cmdbuf));
  ezcmd_get(&cmd);
  
  /* Extract first argument, 
   * which is typically the command
   */

  char* arg = cmd.line;
  printf("Command %s\n", arg);
  
  /* Get the rest of the arguments */

  int arg_number=0;
  for( ;; )
    {
      char* arg = ezcmd_next_arg(&cmd);

      /* No more arguments? */

      if (arg == NULL)
        {
          break;
        }

      /* Nope, still an argument */

      printf("Arg %d: %s\n", arg_number++, arg );
    }

  return 0;
}