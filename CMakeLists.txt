cmake_minimum_required(VERSION 2.8)
set (PROJECT_NAME "BlockEditor")
project(${PROJECT_NAME})

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")


# Install destinations
set( CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install CACHE PATH "Installation Destination" FORCE)
set( INSTALL_DES ./ CACHE PATH "Where to install to." )

# Debug is default
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE ) #MinSizeRel
endif()
message("CMAKE_BUILD_TYPE ::" ${CMAKE_BUILD_TYPE})

add_definitions(
    #-fPIC
    -std=c++11
    #-DUSING_PCH
)

# ============================================
### Source files
file(GLOB SRC_DET "src/*.cpp")
file(GLOB INCL_DET "include/*.h")

# Create nice groups in IDEs
#source_group("UI Files" FILES ${UI_FILES})
#source_group("UI Headers" FILES ${UI_HEADERS})

set(SRC ${SRC_DET})
set(INCL ${INCL_DET})

message("SRC ::" ${SRC})
message("INCL ::" ${INCL})

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
                    )
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#aux_source_directory(. SOURCE_FILES)


# ============================================
# Find includes in corresponding build directories
# Find packages

### Qt5
find_package(Qt5Widgets REQUIRED)
#INCLUDE(${QT_USE_FILE})
set(CMAKE_AUTOMOC ON)
#add_definitions(${QT_DEFINITIONS})
#set(QT_USE_QMAIN true)
#set(QT_PRECOMPILED_HEADER ${PC_HEADER}.h)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
# Use Qt UI files
#qt5_wrap_ui(UI_HEADERS ${UI_FILES})


### Lua State
include_directories("libs/LuaState/include")

### Boost
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

### LuaJIT
find_package(LuaJIT REQUIRED)
include_directories(${LUA_INCLUDE_DIR})


# ============================================

MESSAGE("add_executable of ::" ${PROJECT_NAME})
MESSAGE("SRC ::" ${SRC})
MESSAGE("INCLUDE ::" ${INCL})
SET( SRCS ${INCL} ${SRC})
ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS} )



# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
#TARGET_LINK_LIBRARIES(${PROJECT} ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY} )


# Must be after executable is created!
#qt5_use_modules (
#       ${PROJECT}
#        Widgets
#)



# Boost
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARY})

# Add precompiled header
#add_precompiled_header(${PROJECT} ${PC_HEADER}.h FORCEINCLUDE)


# Compile lua files
#add_custom_command(
#	TARGET ${PROJECT}
#	PRE_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#		${CMAKE_SOURCE_DIR}/scripts $<TARGET_FILE_DIR:Grapedit>/scripts)



# =============================================
### install
INSTALL(TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION ${INSTALL_DES} COMPONENT Runtime )












