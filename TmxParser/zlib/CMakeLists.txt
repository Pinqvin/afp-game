set(ZLIB_SRC
    adler32.c
    crc32.c
    deflate.c
    gzclose.c
    gzlib.c
    gzwrite.c
    inffast.c
    zutil.c
    compress.c
    gzread.c
    infback.c
    inflate.c
    inftrees.c
    trees.c
    uncompr.c)

set(ZLIB_HDR
    inffixed.h
    inflate.h
    inftrees.h
    trees.h
    zconf.h
    crc32.h
    deflate.h
    gzguts.h
    inffast.h
    zlib.h
    zutil.h)

add_library(zlib ${ZLIB_HDR} ${ZLIB_SRC})
