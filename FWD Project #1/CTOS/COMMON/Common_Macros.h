#ifndef COMMON_MACROS
#define COMMON_MACROS

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG&=(~((uint32)(1<<BIT))))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
#define ROR(REG,num) ( REG = (REG>>num) | (REG << ((sizeof(REG) * 8)-num)) )
#define ROL(REG,num) ( REG = (REG<<num) | (REG >> ((sizeof(REG) * 8)-num)) )
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile uint16_t *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile uint8_t *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
              (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))

//*****************************************************************************

#endif
