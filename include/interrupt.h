#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

typedef void (*Execption_Handler) (void);

void __trigger_CtxSwitch_Check(void);
#endif
