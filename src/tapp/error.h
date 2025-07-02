#ifndef TAPP_ERROR_H_
#define TAPP_ERROR_H_

#include <stddef.h>
#include <stdbool.h>

typedef int TAPP_error;

/* Return true if the error code indicates success and false otherwise. */
bool TAPP_check_success(TAPP_error error);

/*
 * Fill a user-provided buffer with an implementation-defined string explaining the error code. No more than maxlen-1
 * characters will be written. If maxlen is greater than zero, then a terminating null character is also
 * written. If fewer characters were written than in the full explanation (i.e. the output is truncated), then the
 * number of characters required (including the terminating null character) is returned in maxlen. Also, if maxlen != 0
 * an error code is returned (TODO: which one).
 */
TAPP_error TAPP_explain_error(TAPP_error error,
                              size_t* maxlen,
                              char* message);

#endif /* TAPP_ERROR_H_ */
