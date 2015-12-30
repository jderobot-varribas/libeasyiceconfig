/*
 *  Copyright (C) 2015-2016 JDE Developers Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see http://www.gnu.org/licenses/.
 *  Authors :
 *       Victor Arribas Raigadas <.varribas.urjc@gmail.com>
 */

#ifndef EASYICECONFIG_INJECTOR_H
#define EASYICECONFIG_INJECTOR_H

#include <string>

#if 0 //__cplusplus >= 201103L
#include <regex>
#else
#include <boost/regex.hpp>
#endif

#include <Ice/Properties.h>

namespace easyiceconfig{
namespace injector{

std::string changePort(std::string endpoint, int port);
std::string changePort(std::string endpoint, std::string port);

void injectPort(Ice::PropertiesPtr, std::string attr, int port);
void injectPort(Ice::PropertiesPtr, std::string attr, std::string port);

}}//NS


#endif // EASYICECONFIG_INJECTOR_H
