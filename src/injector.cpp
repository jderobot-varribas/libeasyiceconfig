/*
 *  Copyright (C) 2016 JDE Developers Team
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


#include "easyiceconfig/injector.hpp"

namespace easyiceconfig{
namespace injector{

std::string
changePort(std::string endpoint, int port){
    std::stringstream ss;
    ss << port;

    return changePort(endpoint, ss.str());
}


std::string
changePort(std::string endpoint, std::string port){
    std::stringstream out;
    port = "-p "+port;

#if 0 //__cplusplus >= 201103L
    std::regex regex("-p [0-9]+");
    //std::regex_replace(std::ostreambuf_iterator<char>(out), endpoint.begin(), endpoint.end(), regex, port);
#else
    boost::regex regex("-p [0-9]+");
    boost::regex_replace(std::ostreambuf_iterator<char>(out), endpoint.begin(), endpoint.end(), regex, port);
#endif
    return out.str();
}



void
injectPort(Ice::PropertiesPtr prop, std::string attr, int port){
    prop->setProperty(attr, changePort(prop->getProperty(attr), port));
}

void
injectPort(Ice::PropertiesPtr prop, std::string attr, std::string port){
    prop->setProperty(attr, changePort(prop->getProperty(attr), port));
}



}}//NS
