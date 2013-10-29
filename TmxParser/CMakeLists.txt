set(TMXPARSER_SRC
    TmxEllipse.cpp
    TmxImage.cpp
    TmxImageLayer.cpp
    TmxLayer.cpp
    TmxMap.cpp
    TmxObject.cpp
    TmxObjectGroup.cpp
    TmxPolygon.cpp
    TmxPolyline.cpp
    TmxPropertySet.cpp
    TmxTile.cpp
    TmxTileset.cpp
    TmxUtil.cpp)

set(TMXPARSER_HDR
    TmxEllipse.h
    Tmx.h
    TmxImage.h
    TmxImageLayer.h
    TmxLayer.h
    TmxMap.h
    TmxMapTile.h
    TmxObjectGroup.h
    TmxObject.h
    TmxPoint.h
    TmxPolygon.h
    TmxPolyline.h
    TmxPropertySet.h
    TmxTile.h
    TmxTileset.h
    TmxUtil.h)

add_subdirectory(zlib)
add_subdirectory(tinyxml)
add_subdirectory(base64)

include_directories(zlib)
include_directories(tinyxml)
include_directories(base64)

add_library(TmxParser ${TMXPARSER_SRC} ${TMXPARSER_HDR})

target_link_libraries(TmxParser zlib tinyxml base64)
