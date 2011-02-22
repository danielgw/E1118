app		:= display-training
src		:= ../../../..
appsrc		:= $(src)/apps/display-training
CONFIG		:= xplain
TOOLCHAIN	:= GNU

ifeq ($(TOOLCHAIN),GNU)
include $(src)/make/app-gnu.mk
endif
ifeq ($(TOOLCHAIN),IAR)
include $(src)/make/app-iar.mk
endif
