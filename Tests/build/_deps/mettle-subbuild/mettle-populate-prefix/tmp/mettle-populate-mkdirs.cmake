# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-src")
  file(MAKE_DIRECTORY "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-build"
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix"
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/tmp"
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/src/mettle-populate-stamp"
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/src"
  "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/src/mettle-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/src/mettle-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Ivan/Documents/GitHub/OS_Lab2/Tests/build/_deps/mettle-subbuild/mettle-populate-prefix/src/mettle-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
