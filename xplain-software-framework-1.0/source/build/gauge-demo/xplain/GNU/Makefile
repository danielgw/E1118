app		:= gauge-demo
src		:= ../../../..
appsrc		:= $(src)/apps/gauge-demo
CONFIG		:= xplain
TOOLCHAIN	:= GNU

ifeq ($(TOOLCHAIN),GNU)
include $(src)/make/app-gnu.mk
endif
ifeq ($(TOOLCHAIN),IAR)
include $(src)/make/app-iar.mk
endif
