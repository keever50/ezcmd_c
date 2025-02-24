/******************************************************************************
 * Included Files
 ******************************************************************************/

#include "ezcmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

/******************************************************************************
 * Public Functions
 ******************************************************************************/

void ezcmd_start(struct ezcommand *cmd, char *buffer, size_t buffer_len)
{
    memset(cmd, 0, sizeof(struct ezcommand));
    cmd->line    = buffer;
    cmd->maxsize = buffer_len;
}

char *ezcmd_next_arg(struct ezcommand *cmd)
{
  /* When no context, make it the begin */

  if (cmd->_context == NULL)
    {
      cmd->_context = cmd->line;
    }

  char *arg = strchr(cmd->_context, 0) + 1;
  if ((size_t)(arg - cmd->line) >= cmd->actualsize)
    {
      return 0;
    }

  cmd->_context = arg;
  return arg;
}

void ezcmd_get(struct ezcommand *cmd)
{
  size_t linepos = 0;
  for (; ; )
    {
      char c = ezcmd_getc();

      if (c == '\b')
        {
          if (linepos > 0)
            {
              cmd->line[linepos--] = 0;
            }
        }
      else if (c == '\r' || c == '\n')
        {
          cmd->line[linepos++] = 0;
          cmd->actualsize      = linepos;
          return;
        }
      else if (c == ' ')
        {
          if (linepos <= cmd->maxsize)
            {
              cmd->line[linepos++] = 0;
            }
        }
      else if (c == 0)
        {
          continue;
        }
      else
        {
          if (linepos <= cmd->maxsize)
            cmd->line[linepos++] = c;
        }
    }
}

void ezcmd_restart(struct ezcommand *cmd)
{
  cmd->_context = NULL;
}

size_t ezcmd_get_parse(struct ezcommand *cmd, char *in, size_t size)
{
  size_t linepos = 0;
  for (size_t i = 0; i < size; i++)
    {
      char c = in[i];

      if (c == '\b')
        {
          if (linepos > 0)
            {
              cmd->line[linepos--] = 0;
            }
        }
      else if (c == '\r' || c == '\n')
        {
          cmd->line[linepos++] = 0;
          cmd->actualsize      = linepos;
          break;
        }
      else if (c == ' ')
        {
          if (linepos <= cmd->maxsize)
            {
              cmd->line[linepos++] = 0;
            }
        }
      else
        {
          if (linepos <= cmd->maxsize)
            {
              cmd->line[linepos++] = c;
            }
        }
    }

  return cmd->actualsize;
}
