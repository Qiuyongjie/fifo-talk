

#ifndef __IOTPANDA_H__
#define __IOTPANDA_H__

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <math.h>
#define sys_quit(str) {\
	perror(str);\
	exit(-1);\
}

#define e_success					exit(EXIT_SUCCESS)
#define e_failure 					exit(EXIT_FAILURE)

#define e_numberic(num) 		    exit(num)
#define err_arg_quit(STRFMT,arg) { \
	fprintf(stderr,STRFMT,arg); \
	exit(-1);\
}

/*static void inline sys_quit2(const char *s)
{
	perror(s);
	exit(-1);
}*/


#endif
