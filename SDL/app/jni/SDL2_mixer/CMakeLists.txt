if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the SDL_mixer source code and call cmake from there")
endif()

##### general #####
cmake_minimum_required(VERSION 3.0)
project(SDL_mixer C)

# include(GNUInstallDirs)
# include(CMakePackageConfigHelpers)

find_package(SDL2 REQUIRED)

set(SDL_MIXER_MAJOR_VERSION 2)
set(SDL_MIXER_MINOR_VERSION 0)
set(SDL_MIXER_MICRO_VERSION 8)
set(SDL_MIXER_INTERFACE_AGE 0)
set(SDL_MIXER_BINARY_AGE 14)
set(SDL_MIXER_VERSION "${SDL_MIXER_MAJOR_VERSION}.${SDL_MIXER_MINOR_VERSION}.${SDL_MIXER_MICRO_VERSION}")

##### library generation #####
add_library(SDL2_mixer SDL2_mixer.h)
target_link_libraries(SDL2_mixer SDL2::SDL2)
target_include_directories(SDL2_mixer PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/SDL2>)

#install(
#  TARGETS SDL2_mixer
#  EXPORT SDL2_mixerTargets
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
#install(
#  FILES SDL2_mixer.h
#  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SDL2
#)
#
###### export files #####
#if (APPLE)
#  set(PKG_PREFIX "SDL2_mixer.framework/Resources")
#elseif (WIN32)
#  set(PKG_PREFIX "cmake")
#else ()
#  set(PKG_PREFIX "lib/cmake/SDL2")
#endif ()
#
#write_basic_package_version_file("${CMAKE_BINARY_DIR}/SDL2_mixerConfigVersion.cmake"
#  VERSION ${SDL2_mixer_VERSION}
#  COMPATIBILITY AnyNewerVersion
#)
#
#install(
#  EXPORT SDL2_mixerTargets
#  FILE SDL2_mixerTargets.cmake
#  NAMESPACE SDL2_mixer::
#  DESTINATION ${PKG_PREFIX}
#)
#install(
#  FILES
#    ${CMAKE_CURRENT_SOURCE_DIR}/SDL2_mixerConfig.cmake
#    ${CMAKE_BINARY_DIR}/SDL2_mixerConfigVersion.cmake
#  DESTINATION ${PKG_PREFIX}
#  COMPONENT Devel
#)
#
###### pkg-config #####
#if (PKG_CONFIG_FOUND)
#  set(SDL_VERSION 2.0.0)
#  set(prefix ${CMAKE_INSTALL_PREFIX})
#  set(exec_prefix "\${prefix}")
#  set(libdir "\${exec_prefix}/lib${LIB_SUFFIX}")
#  set(bindir "\${exec_prefix}/bin")
#  set(includedir "\${prefix}/include")
#
#  configure_file("${SDL2_mixer_SOURCE_DIR}/SDL2_mixer.pc.in"
#    "${SDL2_mixer_BINARY_DIR}/SDL2_mixer.pc" @ONLY)
#
#  if (CMAKE_SYSTEM_NAME MATCHES FreeBSD)
#    # FreeBSD uses ${PREFIX}/libdata/pkgconfig
#    install(FILES ${SDL2_mixer_BINARY_DIR}/SDL2_mixer.pc DESTINATION "libdata/pkgconfig")
#  else ()
#    install(FILES ${SDL2_mixer_BINARY_DIR}/SDL2_mixer.pc
#      DESTINATION "lib${LIB_SUFFIX}/pkgconfig")
#  endif ()
#endif ()
