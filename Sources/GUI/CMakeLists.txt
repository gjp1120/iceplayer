include(FindPkgConfig)

set(ICEPLAYER_GUI_API_VERSION "0.1.0")

set(ICEPLAYER_GUI_ABI_VERSION "0.1.0")
set(ICEPLAYER_GUI_ABI_MAJOR_VERSION "0")

set(ICEPLAYER_GUI_SRC
  gui.c
  gui_listview.c
  about.c
  init.c
)

pkg_search_module(GTK REQUIRED gtk+-2.0)
if(${GTK_FOUND})
  include_directories(${GTK_INCLUDEDIR})
else()
  message('Gtk+ not found!')
endif()


add_library(iceplayer_gui SHARED ${ICEPLAYER_GUI_SRC})
target_link_libraries(iceplayer_gui
                      pthread
                      ${GTK_LIBRARIES})
set_target_properties(iceplayer_gui PROPERTIES
    VERSION ${ICEPLAYER_GUI_ABI_VERSION}
    SOVERSION ${ICEPLAYER_GUI_ABI_MAJOR_VERSION}
    LINK_FLAGS ${CMAKE_SHARED_LINKER_FLAGS}
)

if (ENABLE_STATIC)

add_library(iceplayer_gui-static STATIC ${ICEPLAYER_GUI_SRC})
SET_TARGET_PROPERTIES(iceplayer_gui-static PROPERTIES
    OUTPUT_NAME "iceplayer_gui"
    PREFIX "lib"
)

install(TARGETS iceplayer_gui-static
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)
endif (ENABLE_STATIC)
install(TARGETS iceplayer_gui
    LIBRARY DESTINATION ${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
)
