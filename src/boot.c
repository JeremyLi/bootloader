#include "types.h"
#include "arch.h"
#include "utils.h"
#include "cmsis_device.h"

void abort(void)
{
	while(1);
}


void
__attribute__((noreturn, weak))
assert_failed (u8* file, u32 line)
{
  DBG ("assert_param() failed: file \"%s\", line %d\n", file, line);
  abort ();
  /* NOTREACHED */
}

//extern uint32_t __global_heap__;
int __attribute__ ((section(".after_vectors")))
_relocate(uword ram_image_start)
{
	if (ram_image_start & 0x00000003) {
		DBG("not 4 bytes aligned...\n");
		return -1;
	}
	int i = 0;
	u8* rbegin = (u8*)__data_array_start[0];
	u8* fbegin = (u8*)__data_array_start[1];

	for(i=0; i<__data_array_start[2]; i++) {
		rbegin[i] = fbegin[i];
	}
	rbegin = (u8*) __bss_array_start[0];
//	memcpy(__data_array_start[0], __data_array_start[1], __data_array_start[2]);
	for(i=0; i<__bss_array_start[1]; i++) {
		rbegin[i] = 0;
	}
//	memset(__bss_array_start[0], 0, __bss_array_start[1]);
//	memcpy((u8*)ram_image_start, (u8*)(__bootloader_end[0]+BOOTLOADER_KERNEL_IMAGE_GAP_LEN), __bootloader_end[1]);
	//uword offset = ram_image_start - __image_copy_start;
/*
	uword* rel_start = NULL;
	uword rel_addr = 0;
	uword rel_flag = 0;
	for (rel_start = (uword*)__rel_dyn_start; rel_start < (uword*)__rel_dyn_end; rel_start+=2) {
		rel_addr = *rel_start;
		rel_flag = *(rel_start + 1);
		if ((rel_flag & 0x000000ff) != 0x17)
			continue;
			rel_addr += offset;
		rel_flag = *(uword*)(rel_addr);
		*(uword*)rel_addr = rel_flag + offset;
	}
*/
//	for (uword i = __bss_region_start; i < __bss_region_end; i++) {
//		*(u8*)(i + offset) = 0;
//	}
/*
	uword __global_heap_addr__ = __bss_region_end + offset;
	if (__global_heap_addr__ & 0x00000003)
		__global_heap__ = (__HeapNode_t*) ((__global_heap_addr__ & ~0x00000003) + 0x00000004); ////Align(4)
*/
	return 0;
}


//int __attribute__ ((section(".after_vectors")))
//_relocate_vectors(uint8_t* vectors_start)
//{
//	if (vectors_start & 0x00000003) {
//			DBG("not 4 bytes aligned...\n");
//			return -1;
//		}
//	//	uint32_t i = 0;
//	//	for (i = __image_copy_start; i < __image_copy_end; i++){
//	//		*ram_image_start = *(__image_copy_start + i);
//	//		ram_image_start++;
//	//	}
//	__kmemcpy(vectors_start, __vectors_start, __vectors_end - __vectors_start);
//	return 0;
//}

struct kernel_layout
{
	uword isr_lma;
	uword isr_vma;
	uword isr_size;

	uword text_lma;
	uword text_vma;
	uword text_size;

	uword data_lma;
	uword data_vma;
	uword data_size;

	uword bss_vma;
	uword bss_size;

//	uword kernel_entry;
};

uword _load_kernel(uword kernel_addr)
{
	__attribute__((noreturn)) void (*__ram_kernel)(void);

	struct kernel_layout* layout = (struct kernel_layout*)kernel_addr;
	int i = 0;
	u8* rbegin = layout->isr_vma;
	u8* fbegin = layout->isr_lma;
	u32 len = layout->isr_size;
	for (i=0; i<len; i++) {
		rbegin[i] = fbegin[i];
	}

	rbegin = layout->text_vma;
	fbegin = layout->text_lma;
	len = layout->text_size;
	for (i=0; i<len; i++) {
		rbegin[i] = fbegin[i];
	}

	rbegin = layout->data_vma;
	fbegin = layout->data_lma;
	len = layout->data_size;
	for (i=0; i<len; i++) {
		rbegin[i] = fbegin[i];
	}
//	memcpy(layout->isr_vma, layout->isr_lma, layout->isr_size);
//	memcpy(layout->text_vma, layout->text_lma, layout->text_size);
//	memcpy(layout->data_vma, layout->data_lma, layout->data_size);
	rbegin = layout->bss_vma;
//	fbegin = layout->text_lma;
	len = layout->bss_size;
	for (i=0; i<len; i++) {
		rbegin[i] = 0;
	}
//	memset(layout->bss_vma, 0, layout->bss_size);
	__ram_kernel = layout->text_vma | 0x01; ///non-generic loader
	(*__ram_kernel)();
	return 0;
}

void __attribute__ ((section(".after_vectors"),noreturn))
_boot(void)
{
	// Initialise hardware right after reset, to switch clock to higher
	// frequency and have the rest of the initialisations run faster.
	//
	// Mandatory on platforms like Kinetis, which start with the watch dog
	// enabled and require an early sequence to disable it.
	//
	// Also useful on platform with external RAM, that need to be
	// initialised before filling the BSS section.

	// __initialize_hardware_early (); ////maybe need init ram...
	uword ram_base = RAM_BASE + 0x10000;
	if (ram_base & 0x00000003)
	  ram_base = (ram_base & ~0x00000003) + 0x00000004; ////Align(4)

	int ret = _relocate(ram_base);
	if (ret < 0) {
		DBG("relocate code error!!!\n");
		// return; //maybe halt;
		asm("bkpt");
	}

	Stm32_Clock_Init(336, 8, 2, 7);
	__uart_init(84, 115200);
	DBG("booting...\n");

#define KERNEL_BASE 0x08004000
	ret = _load_kernel(KERNEL_BASE);
	//SCB->VTOR = __vectors_start - __image_copy_start + ram_base;
	////reset msp
//	asm volatile (
//		"ldr r0, %0\n"
//		"ldr r0, [r0]\n"
//		"msr msp, r0\n"
//		::"m"(_estack):"r0"
//	);

}
