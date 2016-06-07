/*
 *
 *
 *
 */

#ifndef OTP_PROTO
#define OTP_PROTO

#define DEBUG 0
#define LOGTOSCREEN 0
#define BUFSZ 1024

#define KEYSETLEN 27
#define KEYSET "ABCDEFGHIJKLMNOPQRSTUVWXYZ "

#define ENCODE 1
#define DECODE 2

#define LOGFILE "logs/program_log"

/* The length of commands (3 chars) is currently hard-coded in some
 * of the parsing functions.  TODO: find a way around that.
 *
 * Until then all commands must be 3 characters long.
 * Responses can be any length.
 * */
#define KEY_CMD "KEY"
#define FILE_CMD "FIL"
#define CLOSE_CMD "CLO"
#define RECONNECT_CMD "RCN"
#define FUNCTION_CMD "FUN"

#define OK_RESPONSE "OK"
#define BAD_RESPONSE "ERR"
#define DATA_RESPONSE "DATA"

#endif
