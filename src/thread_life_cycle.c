#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>

#include"tlc.h"
#include<common.h>

/*
 * Global variable definitions
 */

pthread_t tid1, tid2;
pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;

/*
 * function definitions
 */

void key_init()
{
	pthread_key_create(&key, (void (*)(void *))NULL);
	
	printf("********** KEY INIT DONE ************");
	return;
}

void set_private_data(char *data)
{
	pthread_setspecific(key, (void *)data); 
	return;
}

void print_private_data()
{
	PRINT("%s", (char *)pthread_getspecific(key)); 
	return;
}
	
void *thread1_start(void *args)
{
	thread1_args_t *arg = args;
	thread1_ret_val_t *ret;

	pthread_cleanup_push(thread1_cleanup1, (void *)NULL);
	pthread_cleanup_push(thread1_cleanup2, (void *)NULL);
	pthread_cleanup_push(thread1_cleanup3, (void *)NULL);

	PRINT_THREAD_START("Thread 1")	
	PRINT_THREAD1_ARGS(arg)

	pthread_once(&init_done, key_init);
	set_private_data("++++++   THREAD 1    ++++++");
	print_private_data();

	ret = (thread1_ret_val_t *)calloc(sizeof(thread1_ret_val_t), 1);
	ret->retval = 100;
	strncpy (ret->msg, "Thread1 returning 100", sizeof(ret->msg));
	
	SLEEP_LOOP(1000)

	return (ret);				// thread exiting by returning from its start function-
								//		cleanup handler functions not called
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

void *thread2_start(void *args)
{
	thread2_args_t *arg = args;
	thread2_ret_val_t *ret;

	DEBUG("%d", arg->j);
	pthread_cleanup_push(thread2_cleanup1, (void *)NULL);
	pthread_cleanup_push(thread2_cleanup2, (void *)NULL);
	pthread_cleanup_push(thread2_cleanup3, (void *)NULL);

	PRINT_THREAD_START("Thread 2")	
	PRINT_THREAD2_ARGS(arg)

	pthread_once(&init_done, key_init);
	set_private_data("++++++   THREAD 2    ++++++");
	print_private_data();

	ret = (thread2_ret_val_t *)calloc(sizeof(thread2_ret_val_t), 1);
	ret->retval = 200;
	strncpy (ret->msg, "Thread2 returning 200", sizeof(ret->msg));

	SLEEP_LOOP(1000)
	pthread_exit (ret);			// thread exiting through pthread_exit- 
								// 		cleanup handler functions executed

	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

/*
typedef struct thd_attr {
	int set;
	char attr_name[THD_ATTR_NAME_MAX_LEN];
	
	

} thd_attr_t;
*/

void print_all_thread_attributes()
{
	// pthread_attr_getdetachstate(
	
	return; 
}

int create_threads()
{
	int err;
	thread1_args_t *t1_argp;
	thread2_args_t *t2_argp;
	pthread_attr_t thd_attr;

	t1_argp = (thread1_args_t *) calloc (sizeof(thread1_args_t), 1);
	t2_argp = (thread2_args_t *) calloc (sizeof(thread2_args_t), 1);

	if (!t1_argp || !t2_argp) {
		PRINT_ERR("Error allocating memory", errno)
		return RC_FAILURE;
	}

	/* Create Thread 1 */
	//	SET_THREAD_ATTR(attr);
	pthread_attr_init(&thd_attr);
	pthread_attr_setdetachstate(&thd_attr, PTHREAD_CREATE_DETACHED);

	print_all_thread_attributes();

	//pthread_attr_setdetachstate(&thd_attr, PTHREAD_CREATE_JOINABLE);

	t1_argp->i = 10;
	strncpy (t1_argp->msg, "Thread1 Args", sizeof(t1_argp->msg));

	err = pthread_create(&tid1, (void *)&thd_attr, thread1_start, (void *)t1_argp);
	if (err != 0) {
		PRINT_ERR("Error creating Thread1", err)
		return RC_FAILURE;
	} 
	DEBUG("%d", t1_argp->i);

	// Create Thread 2
	t2_argp->j = 20;
	strncpy (t2_argp->msg, "Thread2 Args", sizeof(t2_argp->msg));

	err = pthread_create(&tid2, (void *)NULL, thread2_start, (void *)t2_argp);
	if (err != 0) {
		PRINT_ERR("Error creating Thread2", err)
		return RC_FAILURE;
	} 
	DEBUG("%d", t2_argp->j);
	
	return RC_SUCCESS;
}

int cancel_threads()
{
	int err;

	err = pthread_cancel(tid1);
	if (err != 0) {
		PRINT_ERR("Error canceling Thread1", err)
		return RC_FAILURE;
	} 

	return RC_SUCCESS;
}

int join_threads()
{
	int err;
	thread1_ret_val_t *t1_retp;
	thread2_ret_val_t *t2_retp;

	err = pthread_join(tid1, (void **)&t1_retp);
	if (err != 0) {
		PRINT_ERR("Error joining Thread1", err)
		return RC_FAILURE;
	} else {
		PRINT_THREAD1_RET(t1_retp)
	} 

	err = pthread_join(tid2, (void **)&t2_retp);
	if (err != 0) {
		PRINT_ERR("Error joining Thread2", err)
		return RC_FAILURE;
	} else {
		PRINT_THREAD2_RET(t2_retp)
	} 

	return RC_SUCCESS;
}

int main(int argc, char *argv[])
{
	int err;

	pthread_key_create(&key, (void *)NULL);
	
	PROG_START
	PRINTARGS(argc, argv)

	// Create threads
	if ((err = create_threads()) != RC_SUCCESS) {
		EXIT(EXC_ERR1);
	} 
	pthread_once(&init_done, key_init);
	
	set_private_data("++++++   ROOT THREAD    ++++++");
	print_private_data();
	
	// Cancel threads
	getchar();
	if ((err = cancel_threads()) != RC_SUCCESS) {
		EXIT(EXC_ERR2);
	} 
		
	// Join threads
	if ((err = join_threads()) != RC_SUCCESS) {
		EXIT(EXC_ERR2);
	} 
		
	return 0;
} 

