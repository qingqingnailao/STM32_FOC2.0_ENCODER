
#ifndef STM103REG
#define STM103REG
#include "TYPESTRUCT.h"


/**********************************************/
/* MACRO DEFINE */
#define __UMEM8(addr)  (*((volatile unsigned char  *)addr))
#define __UMEM16(addr) (*((volatile unsigned short *)addr))
#define __UMEM32(addr) (*((volatile unsigned long  *)addr))

/* SPECIAL REGISTER DEFINE */
#define    PASET	__UMEM32(0x40010810)
#define    PARESET	__UMEM32(0x40010814)
#define    PAIN		__UMEM32(0x40010808)

#define    PBSET	__UMEM32(0x40010C10)
#define    PBRESET	__UMEM32(0x40010C14)
#define    PBIN		__UMEM32(0x40010C08)

#define    PCSET	__UMEM32(0x40011010)
#define    PCRESET	__UMEM32(0x40011014)
#define    PCIN		__UMEM32(0x40011008)

#define    PDOUT	__UMEM32(0x4001140C)
#define    PDSET	__UMEM32(0x40011410)
#define    PDRESET	__UMEM32(0x40011414)
#define    PDIN		__UMEM32(0x40011408)

#define    PESET	__UMEM32(0x40011810)
#define    PERESET	__UMEM32(0x40011814)
#define    PEIN		__UMEM32(0x40011808)

/*************************引脚宏定义****************************/
/******************GPIOA********************/
#define PAI_H2A					GPIO_Pin_0 
#define PAI_H2B					GPIO_Pin_1
#define PAI_H2C					GPIO_Pin_2
#define PAIA_M2IA				GPIO_Pin_3
#define PAIA_M2IB					GPIO_Pin_4
#define PAIA_M2IC					GPIO_Pin_5
//#define PAIA_ITOTAL 			GPIO_Pin_6
#define PAO_T8CH1N 				GPIO_Pin_7

#define PAO_T1CH1 				GPIO_Pin_8
#define PAO_T1CH2 				GPIO_Pin_9
#define PAO_T1CH3 				GPIO_Pin_10
//#define PAO_LCDRS 				GPIO_Pin_11
//#define PAO_LCDEN 				GPIO_Pin_12
//#define PAO_LCDDB0 				GPIO_Pin_15
/******************GPIOB********************/
#define PBO_T8CH2N				GPIO_Pin_0 
#define PBO_T8CH3N				GPIO_Pin_1
//#define PBO_LCDDB5				GPIO_Pin_3
#define PBO_DA1					GPIO_Pin_4
#define PBO_DA2					GPIO_Pin_5
#define PBI_H1A					GPIO_Pin_6
#define PBI_H1B					GPIO_Pin_7
#define PBI_H1C					GPIO_Pin_8

//#define PBO_LCDCS2 				GPIO_Pin_9
//#define PBI_KDOWN 				GPIO_Pin_10
//#define PBO_MBREAK 				GPIO_Pin_11
//#define PBO_M_EN 				GPIO_Pin_12
#define PBO_T1CH1N 				GPIO_Pin_13
#define PBO_T1CH2N 				GPIO_Pin_14
#define PBO_T1CH3N 				GPIO_Pin_15

/******************GPIOC********************/
#define PCIA_M1IA				GPIO_Pin_0 
#define PCIA_M1IB				GPIO_Pin_1
#define PCIA_M1IC				GPIO_Pin_2
#define PCIA_VBUS				GPIO_Pin_3
#define PCIA_VR1				GPIO_Pin_4
#define PCIA_VR2				GPIO_Pin_5

#define PCO_T8CH1				GPIO_Pin_6
#define PCO_T8CH2				GPIO_Pin_7

#define PCO_T8CH3 				GPIO_Pin_8
#define PCO_STX 				GPIO_Pin_9
#define PCI_SRX 				GPIO_Pin_10
#define PCI_EXT1 				GPIO_Pin_11
//#define PCO_LCDDB3				GPIO_Pin_12
//#define PCO_T1CH2N 				GPIO_Pin_14
//#define PCI_KSET 				GPIO_Pin_15
/******************GPIOD********************/
#define PDO_D2					GPIO_Pin_0 
#define PDO_D3					GPIO_Pin_1
#define PDI_EXT2				GPIO_Pin_2
//#define PDIA_VBUS				GPIO_Pin_3
#define PDO_OE					GPIO_Pin_4
#define PDO_WE					GPIO_Pin_5

//#define PDO_T8CH1				GPIO_Pin_6
//#define PDO_T8CH2				GPIO_Pin_7

#define PDO_D13 				GPIO_Pin_8
#define PDO_D14 				GPIO_Pin_9
#define PDO_D15 				GPIO_Pin_10
//#define PDI_EXT1 				GPIO_Pin_11
//#define PDO_LCDDB3				GPIO_Pin_12
#define PDO_DO 					GPIO_Pin_14
#define PDO_D1 					GPIO_Pin_15 
/******************GPIOE********************/
//#define PEIA_M1IA				GPIO_Pin_0 
//#define PEIA_M1IB				GPIO_Pin_1
#define PEO_LED1				GPIO_Pin_2
#define PEO_LED2				GPIO_Pin_3
//#define PEIA_VR1				GPIO_Pin_4
//#define PEIA_VR2				GPIO_Pin_5

//#define PEO_T8CH1				GPIO_Pin_6
#define PEO_D4				GPIO_Pin_7

#define PEO_D5 				GPIO_Pin_8
#define PEO_D6 				GPIO_Pin_9
#define PEO_D7 				GPIO_Pin_10
#define PEO_D8 				GPIO_Pin_11
#define PEO_D9				GPIO_Pin_12
#define PEO_D10				GPIO_Pin_13
#define PEO_D11 			GPIO_Pin_14
#define PEO_D12 			GPIO_Pin_15 
/******************GPIOF********************/
#define PFO_RS				GPIO_Pin_0 
//#define PFIA_M1IB				GPIO_Pin_1
//#define PFIA_M1IC				GPIO_Pin_2
//#define PFIA_VBUS				GPIO_Pin_3
//#define PFIA_VR1				GPIO_Pin_4
//#define PFIA_VR2				GPIO_Pin_5

//#define PFO_T8CH1				GPIO_Pin_6
//#define PFO_T8CH2				GPIO_Pin_7

//#define PFO_T8CH3 				GPIO_Pin_8
//#define PFO_STX 				GPIO_Pin_9
//#define PFI_SRX 				GPIO_Pin_10
#define PFI_K_FUN 				GPIO_Pin_11
#define PFI_K_LEFT				GPIO_Pin_12
#define PFI_K_RIGHT				GPIO_Pin_13
#define PFI_K_UP 				GPIO_Pin_14
#define PFI_K_DOWN 				GPIO_Pin_15 

/******************GPIOG********************/
#define PGI_K_OTH				GPIO_Pin_0 
#define PGO_LRST				GPIO_Pin_1
#define PGO_M1EN				GPIO_Pin_2
#define PGI_M1FAULT				GPIO_Pin_3
#define PGO_M2EN				GPIO_Pin_4
#define PGI_M2FAULT				GPIO_Pin_5

//#define PGO_T8CH1				GPIO_Pin_6
//#define PGO_T8CH2				GPIO_Pin_7

//#define PGO_T8CH3 				GPIO_Pin_8
//#define PGO_STX 				GPIO_Pin_9
//#define PGI_SRX 				GPIO_Pin_10
//#define PGI_EXT1 				GPIO_Pin_11
#define PGO_CS					GPIO_Pin_12
//#define PCO_T1CH2N 				GPIO_Pin_14
//#define PCI_KSET 				GPIO_Pin_15 









/**********************************
   IO定义
***********************************/

/****************P0 Define********************************/

#define LCDRSON()     PASET = PAO_LCDRS
#define LCDRSOFF()    PARESET = PAO_LCDRS

#define LCDENON()      PASET = PAO_LCDEN
#define LCDENOFF()     PARESET = PAO_LCDEN

#define LCDDB0ON()      PASET = PAO_LCDDB0
#define LCDDB0OFF()    	PARESET = PAO_LCDDB0

#define T1CH1ON()      PASET = PAO_T1CH1
#define T1CH1OFF()    	PARESET = PAO_T1CH1

#define T1CH2ON()      PASET = PAO_T1CH2
#define T1CH2OFF()    	PARESET = PAO_T1CH2

#define T1CH3ON()      PASET = PAO_T1CH3
#define T1CH3OFF()    	PARESET = PAO_T1CH3



#define KEY_SET 		((*(volatile TYPE_DWORD*)&PAIN).bit.b7)






//#define LED1    ((*(volatile TYPE_DWORD*)&PBOUT).bit.b10)
#define LCDDB5ON()    	PBSET = PBO_LCDDB5
#define LCDDB5OFF()   	PBRESET = PBO_LCDDB5

#define LCDDB6ON()    	PBSET = PBO_LCDDB6
#define LCDDB6OFF()   	PBRESET = PBO_LCDDB6

#define LCDDB7ON()    	PBSET = PBO_LCDDB7
#define LCDDB7OFF()   	PBRESET = PBO_LCDDB7

#define LCDCS1ON()     	PBSET = PBO_LCDCS1
#define LCDCS1OFF()    	PBRESET = PBO_LCDCS1


#define LCDCS2ON()     	PBSET = PBO_LCDCS2
#define LCDCS2OFF()    	PBRESET = PBO_LCDCS2

#define T1CH1NON()     	PBSET = PBO_T1CH1N
#define T1CH1NOFF()    	PBRESET = PBO_T1CH1N

#define T1CH2NON()     	PBSET = PBO_T1CH2N
#define T1CH2NOFF()    	PBRESET = PBO_T1CH2N

#define T1CH3NON()     	PBSET = PBO_T1CH3N
#define T1CH3NOFF()    	PBRESET = PBO_T1CH3N




#define MBREAKON()     	PBSET = PBO_MBREAK
#define MBREAKOFF()    	PBRESET = PBO_MBREAK

#define MENON()     	PBSET = PBO_M_EN
#define MENOFF()    	PBRESET = PBO_M_EN


#define KEY_RIGHT 		((*(volatile TYPE_DWORD*)&PCIN).bit.b11)
#define KEY_UP 			((*(volatile TYPE_DWORD*)&PDIN).bit.b0)
#define KEY_DOWN 		((*(volatile TYPE_DWORD*)&PDIN).bit.b1)


/***************GPIOC********************/

#define IICSCLON()    	PCSET = PCO_IIC_CLK
#define IICSCLOFF()   	PCRESET = PCO_IIC_CLK

#define IICSDAON()    	PCSET = PCO_IIC_DATA
#define IICSDAOFF()   	PCRESET = PCO_IIC_DATA

#define LEDON()    		PCSET = PCO_LED1
#define LEDOFF()   		PCRESET = PCO_LED1


#define LCDDB1ON()    	PCSET = PCO_LCDDB1
#define LCDDB1OFF()   	PCRESET = PCO_LCDDB1

#define LCDDB2ON()    	PCSET = PCO_LCDDB2
#define LCDDB2OFF()   	PCRESET = PCO_LCDDB2

#define LCDDB3ON()    	PCSET = PCO_LCDDB3
#define LCDDB3OFF()   	PCRESET = PCO_LCDDB3
#define MDEFAULT()		((*(volatile TYPE_DWORD*)&PCIN).bit.b9)

#define KEY_FUN 			((*(volatile TYPE_DWORD*)&PEIN).bit.b11)
#define KEY_LEFT 		((*(volatile TYPE_DWORD*)&PCIN).bit.b12)

/***************GPIOD********************/
#define LCDDB4ON()    	PDSET = PDO_LCDDB4
#define LCDDB4OFF()   	PDRESET = PDO_LCDDB4















#endif

