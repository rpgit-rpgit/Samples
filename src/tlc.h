#ifndef __THREAD_LIFE_CYCLE_H__
#define __THREAD_LIFE_CYCLE_H__

#include"tlc_cleanup.h"

/*
 * Macro definitions
 */

#define	MSGLEN	50

#define SLEEP_LOOP(usec)												\
	{																	\
		while (1) {														\
			usleep(1000);												\
		}																\
	}


#define PRINT_THREAD1_ARGS(arg)											\
	{																	\
		printf(FMT "INPUT ARGS\n\ti=%d\tmsg='%s'\n",					\
			FMTVAR, arg->i, arg->msg);									\
	}

#define PRINT_THREAD2_ARGS(arg)											\
	{																	\
		printf(FMT "INPUT ARGS\n\tj=%d\tmsg='%s'\n",					\
			FMTVAR, arg->j, arg->msg);									\
	}

#define PRINT_THREAD1_RET(arg)											\
	{																	\
		if (arg == PTHREAD_CANCELED) {									\
			printf(FMT "Thread1 return by cancelation\n", FMTVAR);		\
		} else {														\
			printf(FMT "Thread1 Return Values\n\tretval=%d\tmsg='%s'\n",\
				FMTVAR, arg->retval, arg->msg);							\
		}																\
	}

#define PRINT_THREAD2_RET(arg)											\
	{																	\
		if (arg == PTHREAD_CANCELED) {									\
			printf(FMT "Thread2 return by cancelation\n", FMTVAR);		\
		} else {														\
			printf(FMT "Thread2 Return Values\n\tretval=%d\tmsg='%s'\n",\
				FMTVAR, arg->retval, arg->msg);							\
		}																\
	}

#define PRINT_THREAD_CANCELED											\
	{																	\
		printf(FMT "Thread returned upon Cancelation\n", FMTVAR);		\
	}

/*
 * thread input argument structures
 */

typedef struct thread1_args {
	int i;
	char msg[MSGLEN];
} thread1_args_t;

typedef struct thread2_args {
	int j;
	char msg[MSGLEN];
} thread2_args_t;

/*
 * thread return value structures
 */

typedef struct thread1_ret_val {
	int retval;
	char msg[MSGLEN];
} thread1_ret_val_t;

typedef struct thread2_ret_val {
	int retval;
	char msg[MSGLEN];
} thread2_ret_val_t;


/*
 * function declarations
 */

void *thread1_start(void *args);
void *thread2_start(void *args);

void key_init();
void set_private_data(char *data);
void print_private_data();

int create_threads();
int cancel_threads();
int join_threads();


#endif
