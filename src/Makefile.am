## Process this file with automake to produce Makefile.in

include $(top_srcdir)/common.mk

AM_CFLAGS = -Wall -g -I$(ZLOG_DIR)/include -I$(CACACOMUN_DIR)
lib_LTLIBRARIES = libescapecabron.la 
libescapecabron_la_SOURCES = escapecabron.c escapecabron.h

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libescapecabron.la -L$(ZLOG_DIR)/lib -lzlog -lpthread -L$(CACACOMUN_DIR) -lcacacomun 
main_LDFLAGS= -Wl,-stack_size -Wl,4000000

