.PHONY: all debug clean

#######################################
########  TARGET DEFNINATIONS #########
#######################################

ALL_TARGETS=$(ALL_LIBS) $(ALL_APPS)
ALL_TARGETS_DEBUG=$(ALL_LIBS_DEBUG) $(ALL_APPS_DEBUG)

#ALL_LIBS=$(ALL_STATIC_LIBS) $(ALL_SHARED_LIBS)
#ALL_STATIC_LIBS=libqueue.ar
#ALL_SHARED_LIBS=libqueue.so
ALL_APPS=thread_life_cycle

#ALL_LIBS_DEBUG=$(ALL_STATIC_LIBS_DEBUG) $(ALL_SHARED_LIBS_DEBUG)
#ALL_STATIC_LIBS_DEBUG=libqueue_DEBUG.ar
#ALL_SHARED_LIBS_DEBUG=libqueue_DEBUG.so
ALL_APPS_DEBUG=thread_life_cycle_DEBUG


#######################################
#########  RULES DEFNINATIONS #########
#######################################

##### Rules for non-DEBUG targets #####


all:	$(ALL_TARGETS)

thread_life_cycle: $(top_makefile) Makefile $(common_inc_dir)/common.h thread_life_cycle.c
	$(CC) $(CFLAGS) $(INC) thread_life_cycle.c -lpthread -o $@
	install -D $@ $(output_appdir)/$@

#libqueue.ar:	queue.o
#	$(AR) cq $@ queue.o 
#	install -D $@ $(output_static_libdir)/$@
#
#queue.o: $(top_makefile) Makefile queue.c $(inc_dir)/queue.h
#	$(CC) $(CFLAGS) $(INC) -c queue.c
#	install -D $@ $(output_objdir)/$@
#
#queue_static_test: $(top_makefile) Makefile libqueue.ar $(inc_dir)/queue.h $(inc_dir)/common.h queue_test.c
#	$(CC) $(CFLAGS) $(INC) queue_test.c libqueue.ar -o $@
#	install -D $@ $(output_appdir)/$@
#
#libqueue.so:	$(top_makefile) Makefile queue.c $(inc_dir)/queue.h
#	$(CC) $(CFLAGS) $(CFLAGS_SHARED_LIB) $(INC) queue.c -o $@
#	install -D $@ $(output_shared_libdir)/$@
#
#queue_shared_test: $(top_makefile) Makefile libqueue.so $(inc_dir)/queue.h $(inc_dir)/common.h queue_test.c
#	#$(CC) $(CFLAGS) $(INC) queue_test.c -L $(shell pwd) -l queue -o $@
#	$(CC) $(CFLAGS) $(INC) queue_test.c -L . -l queue -l pthread -o $@
#	install -D $@ $(output_appdir)/$@

#################### Rules for DEBUG targets #################

debug:	$(ALL_TARGETS_DEBUG)

thread_life_cycle_DEBUG: $(top_makefile) Makefile $(common_inc_dir)/common.h thread_life_cycle.c
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INC) thread_life_cycle.c -o $@
	install -D $@ $(output_appdir)/$@

#libqueue_DEBUG.ar:	queue_DEBUG.o
#	$(AR) cq $@ queue_DEBUG.o 
#	install -D $@ $(output_static_libdir)/$@
#
#queue_DEBUG.o: $(top_makefile) Makefile queue.c $(inc_dir)/queue.h
#	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INC) -c queue.c -o $@
#	install -D $@ $(output_objdir)/$@
#	
#queue_static_test_DEBUG: $(top_makefile) Makefile libqueue_DEBUG.ar $(inc_dir)/queue.h $(inc_dir)/common.h queue_test.c
#	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(INC) queue_test.c libqueue_DEBUG.ar -o $@
#	install -D $@ $(output_appdir)/$@
#
#libqueue_DEBUG.so:	$(top_makefile) Makefile queue.c $(inc_dir)/queue.h
#	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) $(CFLAGS_SHARED_LIB) $(INC) queue.c -o $@
#	install -D $@ $(output_shared_libdir)/$@
#
#queue_shared_test_DEBUG:
#	echo "TODO 2"


clean:	
	rm -f *.o $(ALL_LIBS) $(ALL_APPS) $(ALL_LIBS_DEBUG) $(ALL_APPS_DEBUG)

