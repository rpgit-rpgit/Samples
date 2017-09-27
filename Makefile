#base_dir=/home/shrini/shrinivas/Dev/my_progs/baseLibs

COMMON_BASE=1
COMMON_BASE_GH_REPO_URL="https://github.com/rpgit-rpgit/common_base.git"

top_makefile=$(base_dir)/Makefile

#######################################
#######  DIRECTORY DECLARATIONS ########
#######################################

base_dir=$(shell pwd)
inc_dir=$(base_dir)/inc
output_dir=$(base_dir)/output
output_objdir=$(output_dir)/obj
output_libdir=$(output_dir)/lib
output_static_libdir=$(output_libdir)/static
output_shared_libdir=$(output_libdir)/shared
output_appdir=$(output_dir)/app

ifdef COMMON_BASE
common_base_dir=$(base_dir)/common_base
common_inc_dir=$(common_base_dir)/inc
endif

SUBDIRS=src

#######################################
#######  FLAGS DECLARATIONS ########
#######################################

AR=ar
CC=gcc
CFLAGS= -O2 -Wall
CFLAGS_DEBUG= -g
CFLAGS_SHARED_LIB= -fpic -c

ifdef COMMON_BASE
INC=-I$(inc_dir) -I$(common_inc_dir)
else
INC=-I$(inc_dir)
endif



#######################################
#########  EXPORT VARIABLES ###########
#######################################
export base_dir
export inc_dir
export common_inc_dir
export output_dir
export output_objdir 
export output_static_libdir 
export output_shared_libdir 
export output_appdir 
export top_makefile
export CFLAGS
export CFLAGS_DEBUG
export CFLAGS_SHARED_LIB
export INC

#.PHONY:	all debug clean cleanAll
.PHONY:	all clean cleanAll


#######################################
###########  TARGET RULES #############
#######################################

all:
	make common_base
	@for d in $(SUBDIRS) ; do							\
		make -C $$d all; 								\
	done

debug:
	make common_base
	@for d in $(SUBDIRS) ; do							\
		make -C $$d debug; 								\
	done

options:
	echo " - COMMON_BASE -" 

ifdef COMMON_BASE
	echo "Common base defined"
else
	echo "Common base not defined"
endif


common_base_forced:
	echo "common_base_forced"
	rm -rf $(common_base_dir)
	git clone $(COMMON_BASE_GH_REPO_URL)
	if [ "$$?" -ne 0 ] ; then							\
		exit 1;											\
	fi													
	make -C $(common_base_dir)	

common_base:
	if [ -d $(common_base_dir) ]; then					\
		echo "Common dir present - $(common_inc_dir)";	\
	else												\
		echo Common dir not present - $(common_inc_dir);\
		git clone $(COMMON_BASE_GH_REPO_URL);			\
		echo Ret2 = $$?;								\
	fi
	make -C $(common_base_dir)
	
common_base_remove:
	echo "common_base_remove"
	rm -rf $(common_base_dir)

clean:
	if [ -d $(common_base_dir) ]; then 					\
		make -C $(common_base_dir) clean;				\
	fi													
	@for d in $(SUBDIRS) ; do							\
		make -C $$d clean; 								\
	done												
	

cleanAll:	clean
	rm -rf $(output_dir)/*
	
