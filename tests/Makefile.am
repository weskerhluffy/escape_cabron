include $(top_srcdir)/common.mk

TESTS = check_escapecabron
check_PROGRAMS = check_escapecabron
check_escapecabron_SOURCES = check_escapecabron.c $(top_builddir)/src/escapecabron.h
check_escapecabron_CFLAGS = @CHECK_CFLAGS@ -g -I$(ZLOG_DIR)/include  -Wall -I$(CACACOMUN_DIR)
check_escapecabron_LDADD = $(top_builddir)/src/libescapecabron.la @CHECK_LIBS@ -L$(ZLOG_DIR)/lib -lzlog -lpthread -L$(CACACOMUN_DIR) -lcacacomun

