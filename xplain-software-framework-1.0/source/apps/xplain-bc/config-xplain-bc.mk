include $(src)/board/xplain-bc/config.mk
include $(src)/apps/xplain-bc/config.mk

CONFIG_CPU_HZ=8000000UL
CONFIG_STACK_SIZE=0x100
CONFIG_NR_BUFFERS=4

CONFIG_DMAPOOL_SMALL_OBJ_SIZE=32
CONFIG_DMAPOOL_NR_SMALL_OBJS=16
CONFIG_DMAPOOL_LARGE_OBJ_SIZE=512
CONFIG_DMAPOOL_NR_LARGE_OBJS=4

CONFIG_AT90USB=y
CONFIG_AT90USB_UDC=y

CONFIG_UDC_FULL_SPEED=y

CONFIG_SPI0=y
CONFIG_BLOCK_DATAFLASH_STATIC_SPI_ID=0
CONFIG_MASS_STORAGE_DATAFLASH_SPI_ID=0

include $(src)/apps/xplain-bc/dataflash.mk

# Debug console stuff
#CONFIG_ASSERT=y
#CONFIG_STREAM=y
#CONFIG_SERIAL_UART=y
#CONFIG_UART_BAUD_RATE=9600
#CONFIG_UART_STREAM=y
#CONFIG_UART_CTRL=y
#CONFIG_DEBUG_CONSOLE=y
#CONFIG_DEBUG_UART=y
#CONFIG_DEBUG_UART_ID=0
#CONFIG_DEBUG_LEVEL=DEBUG_PANIC
