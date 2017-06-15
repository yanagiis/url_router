set(SRC url_tree.c
    url_router.c
    dict.c)

add_library(url_router STATIC ${SRC})

set_target_properties(url_router PROPERTIES
    C_STANDARD 99
    COMPILE_FLAGS -Werror)

install(EXPORT url_router DESTINATION lib)
install(TARGETS url_router
    EXPORT url_router
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
