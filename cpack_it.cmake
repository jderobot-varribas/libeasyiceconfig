#  Copyright (C) 2016 Victor Arribas
#  License: GPLv3 <http://www.gnu.org/licenses/gpl-3.0.html> or above
#  Authors:
#    Victor Arribas <v.arribas.urjc@gmail.com>

cmake_minimum_required(VERSION 2.6)

project(easyiceconfig-dev)

SET (CPACK_PACKAGE_VERSION_MAJOR 0)
SET (CPACK_PACKAGE_VERSION_MINOR 9)
SET (CPACK_PACKAGE_VERSION_PATCH 3-1)

SET (CPACK_PACKAGE_CONTACT "Victor Arribas <v.arribas.urjc@gmail.com>")
SET (CPACK_PACKAGE_DESCRIPTION_SUMMARY
"A library to tame Ice.Config
 You can obtain a copy of source code from: https://github.com/jderobot-varribas/libeasyiceconfig
 .
 Features:
  * allows to load Ice.Config files from *any* place.
  * simplifies Ice Proxy creation and exception managenemt.
 .
 As simple as replace a word and enjoy:
  * Ice::initialize ---> EasyIce::initialize
  * Ice::createProperties ---> EasyIce::createProperties
") 

SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libzeroc-ice35-dev, libzeroc-ice35, libiceutil35")

SET (CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
SET (CPACK_DEBIAN_PACKAGE_SECTION "devel")


SET (CPACK_GENERATOR "DEB")
SET (CPACK_DEBIAN_PACKAGE_SHLIBDEPS OFF)
SET (CPACK_SET_DESTDIR ON)
SET (CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")


include (CPack Documentation)
