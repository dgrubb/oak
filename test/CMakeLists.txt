include(GoogleTest)

enable_testing()
find_package(GTest REQUIRED)

find_library(GMOCK_LIB gmock)
find_library(GMOCK_MAIN_LIB gmock_main)
set(GMOCK_LIBRARIES "${GMOCK_LIB};${GMOCK_MAIN_LIB}")

get_target_property(${PROJECT_NAME}_sources ${PROJECT_NAME} SOURCES)
list(FILTER ${PROJECT_NAME}_sources EXCLUDE REGEX main.cc)
set(${PROJECT_NAME}_TEST_SOURCES utmain.cc
    utCpsr.cc
    utIoc.cc
    utMemc.cc
    utLog.cc
    utRegister.cc
    utRegisterFile.cc
)

add_executable(${PROJECT_NAME}-utmain
    ${${PROJECT_NAME}_TEST_SOURCES}
    ${${PROJECT_NAME}_sources}
)

target_link_libraries(${PROJECT_NAME}-utmain
    GTest::GTest GTest::Main
    ${GMOCK_LIBRARIES}
    ${SDL2_LIBRARIES}
)
target_include_directories(${PROJECT_NAME}-utmain
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../source
        ${CMAKE_CURRENT_LIST_DIR}/../source/chipset
        ${CMAKE_CURRENT_LIST_DIR}/../source/chipset/arm2
        ${CMAKE_CURRENT_LIST_DIR}/../source/util
        ${CMAKE_CURRENT_LIST_DIR}/../include/
        ${CMAKE_CURRENT_LIST_DIR}/../include/chipset
        ${CMAKE_CURRENT_LIST_DIR}/../include/chipset/arm2
        ${CMAKE_CURRENT_LIST_DIR}/../include/chipset/arm2/opcodes
        ${CMAKE_CURRENT_LIST_DIR}/../include/util
)

