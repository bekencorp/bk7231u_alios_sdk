NAME := spiapp

$(NAME)_MBINS_TYPE := app
$(NAME)_VERSION := 1.0.0
$(NAME)_SUMMARY := spiapp

$(NAME)_SOURCES :=   app_entry.c
$(NAME)_COMPONENTS += linkkit_sdk_c

$(NAME)_COMPONENTS += netmgr cjson

$(NAME)_COMPONENTS  += cli


GLOBAL_INCLUDES += ./

