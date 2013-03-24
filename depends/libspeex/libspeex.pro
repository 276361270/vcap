TEMPLATE = lib

include(../../packages/include/common.pri)

CONFIG += staticlib
CONFIG -= qt

INCLUDEPATH += ./
INCLUDEPATH += ./win32
INCLUDEPATH += ./include

DEFINES += HAVE_CONFIG_H
DEFINES += _LIB

# Input
HEADERS += 	\
            cb_search.h       \
            win32/config.h          \
            fftwrap.h         \
            filters.h         \
            filters_ssh.h     \
            kiss_fft.h        \
            kiss_fftr.h       \
            lpc.h             \
            lsp.h             \
            ltp.h             \
            ltp_sse.h         \
            math_approx.h     \
            misc.h            \
            modes.h           \
            nb_celp.h         \
            pseudofloat.h     \
            quant_lsp.h       \
            sb_celp.h         \
            speex.h           \
            speex_bits.h      \
            speex_callbacks.h \
            speex_echo.h      \
            speex_header.h    \
            speex_jitter.h    \
            speex_noglobals.h \
            speex_preprocess.h\
            speex_stereo.h    \
            speex_types.h     \
            stack_alloc.h     \
            vbr.h             \
            vq.h
            

           
SOURCES += 	libspeex/bits.c            \
            libspeex/cb_search.c       \
            libspeex/exc_10_16_table.c \
            libspeex/exc_10_32_table.c \
            libspeex/exc_20_32_table.c \
            libspeex/exc_5_256_table.c \
            libspeex/exc_5_64_table.c  \
            libspeex/exc_8_128_table.c \
            libspeex/fftwrap.c         \
            libspeex/filterbank.c      \
            libspeex/filters.c         \
            libspeex/gain_table.c      \
            libspeex/gain_table_lbr.c  \
            libspeex/hexc_10_32_table.c\
            libspeex/hexc_table.c      \
            libspeex/high_lsp_tables.c \
            libspeex/jitter.c          \
            libspeex/kiss_fft.c        \
            libspeex/kiss_fftr.c       \
            libspeex/lpc.c             \
            libspeex/lsp.c             \
            libspeex/lsp_tables_nb.c   \
            libspeex/ltp.c             \
            libspeex/mdf.c             \
            libspeex/modes.c           \
            libspeex/modes_wb.c        \
            libspeex/nb_celp.c         \
            libspeex/preprocess.c      \
            libspeex/quant_lsp.c       \
            libspeex/sb_celp.c         \
            libspeex/smallft.c         \
            libspeex/speex.c           \
            libspeex/speex_callbacks.c \
            libspeex/speex_header.c    \
            libspeex/stereo.c          \
            libspeex/vbr.c             \
            libspeex/vq.c              \
            libspeex/window.c          \
            
            
            
