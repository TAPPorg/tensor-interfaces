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
 * written. The actual number of characters written is returned, not including the terminating null character.
 * If maxlen is zero, then no characters are written and instead the length of the full string which would have been
 * written is returned, not including the terminating null character. This means that the message written will always
 * be null-terminated.
 *
 * TODO: should the null character be included in the return value?
 */
size_t TAPP_explain_error(TAPP_error error,
                          size_t maxlen,
                          char* message);

#endif /* TAPP_ERROR_H_ */
