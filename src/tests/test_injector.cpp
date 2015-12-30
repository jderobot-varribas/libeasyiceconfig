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
 *      Victor Arribas Raigadas <.varribas.urjc@gmail.com>
 */

#include <iostream>
#include <Ice/Initialize.h>
#include <easyiceconfig/injector.hpp>
#include <easyiceconfig/debug.hpp>


int main(int argc, char* argv[]){
    std::string endpoint = "tcp -h localhost -p 1234";
    std::string endpoint2 = easyiceconfig::injector::changePort(endpoint, 4321);
    std::cout<<"\nTest 1: changePort()\n  before: "<<endpoint<<"\n  after: "<<endpoint2<<std::endl;

    std::cout<<"\nTest 2: injectPort()\n";
    std::string attr = "Demo.Endpoint";
    Ice::PropertiesPtr prop = Ice::createProperties();
    prop->setProperty(attr, endpoint);
    easyiceconfig::debug::printProperties(prop);
    easyiceconfig::injector::injectPort(prop, attr, 5555);
    easyiceconfig::debug::printProperties(prop);
}
