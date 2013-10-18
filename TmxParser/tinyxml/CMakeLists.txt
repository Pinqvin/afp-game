set(TINYXML_SRC
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp)

set(TINYXML_HDR
    tinystr.h
    tinyxml.h)

add_library(tinyxml ${TINYXML_SRC} ${TINYXML_HDR})
