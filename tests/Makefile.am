include $(top_srcdir)/common.mk

TESTS = check_escapecabron
check_PROGRAMS = check_escapecabron
check_escapecabron_SOURCES = check_escapecabron.c $(top_builddir)/src/escapecabron.h
check_escapecabron_CFLAGS = @CHECK_CFLAGS@ -g3 -I$(ZLOG_DIR)/include  -Wall -I$(CACACOMUN_DIR) -std=c99
check_escapecabron_LDADD =  $(top_builddir)/src/libescapecabron.la @CHECK_LIBS@ -lpthread -L$(CACACOMUN_DIR) -lcacacomun  -L$(ZLOG_DIR)/lib -lzlog 

