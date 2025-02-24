#ifndef __EZCMD_H
#define __EZCMD_H

/******************************************************************************
 * Included Files
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * Data structures
 ******************************************************************************/

/* The command structure used to
 * store progress of parsing arguments.
 * Can be initialized using ezcmd_start()
 * It contains the parsing context / state
 * and a pointer to a char buffer with its size.
 * char* line will always contain the current
 * parsed argument
 */

struct ezcommand
{
    char *line;
    size_t maxsize;
    size_t actualsize;
    char *_context;
};

/******************************************************************************
 * User implementation
 ******************************************************************************/

/* The user can implement this to
 * get a character from any device.
 * This does not have to be blocking.
 * No input should return \0
 */

char ezcmd_getc();

/******************************************************************************
 * Public functions
 ******************************************************************************/

/* Initializes the ezcommand structure.
 * Can be ran every time before getting
 * new commands
 */

void ezcmd_start(struct ezcommand *cmd, char *buffer,
                 size_t buffer_len);

/* Get the next argument.
 * Returns NULL when there are no more arguments
 */

char *ezcmd_next_arg(struct ezcommand *cmd);

/* Blocking call to get commands and its arguments
 * by polling the user implemented ezcmd_getc().
 * The first argument can be returned by
 * using char* firstarg = cmd.line;
 * The rest can be extracted using ezcmd_next_arg(&cmd);
 */

void ezcmd_get(struct ezcommand *cmd);

/* Restarts the parser and arguments can be read
 * from the start again.
 */

void ezcmd_restart(struct ezcommand *cmd);

/* This will parse a char string to extract arguments.
 * This will not block because it does not have
 * to wait for inputs unlike ezcmd_get(&cmd);
 */

size_t ezcmd_get_parse(struct ezcommand *cmd, char *in,
                       size_t size);

#endif /* __EZCMD_H */
