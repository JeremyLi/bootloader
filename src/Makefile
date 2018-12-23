SUBDIRS=$(shell ls -l | grep ^d | awk '{if($$9 != "include") print $$9}')

CUR_DIR=$(shell pwd)

CUR_SOURCE=${wildcard *.c}
CUR_ASM_SRC=${wildcard *.s}

CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}
CUR_ASM_OBJS=${patsubst %.s, %.o, $(CUR_ASM_SRC)}

OBJS+=$(CUR_OBJS) $(CUR_ASM_OBJS)

export OBJS

all:$(SUBDIRS) $(OBJS)

$(SUBDIRS):echo
	make -C $@

echo:
	@echo $(SUBDIRS)

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $(BUILD_DIR)/$@
	
%.o:%.s
	$(CC) $(CFLAGS) -c $^ -o $(BUILD_DIR)/$@
	
clean: $(SUBDIRS)
# $(foreach dir, $(SUBDIRS), $(call build-dir $(dir) clean))
# echo cleaning $(CUR_DIR)
	rm -f $(CUR_DIR)/*.o
