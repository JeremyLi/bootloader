#ifndef __ARCH_H__
#define __ARCH_H__

#define RAM_BASE 0x20000000
#define RAM_SIZE 0x20000

#define GAP_VAR_NUM	1
#define BOOTLOADER_KERNEL_IMAGE_GAP_LEN (sizeof(int)*GAP_VAR_NUM)
extern uint32_t _estack;

extern uint32_t __vectors_start__;
extern uint32_t __vectors_end__;
extern uint32_t __text_start__;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _etext;



extern uint32_t __data_start__;
extern uint32_t __data_end__;

extern uint32_t __loader_end__;
extern uint32_t* __kernel_size_ptr__;
extern uint32_t* __kernel_entry_ptr__;
extern uint32_t __bss_start;
extern uint32_t __bss_end;

extern uint32_t __data_array_start[3];
extern uint32_t __bss_array_start[2];
extern uint32_t __bootloader_end[2];


#endif

