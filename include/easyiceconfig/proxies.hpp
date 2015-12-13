/*
 *  Copyright (C) 2015 JDE Developers Team
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

#ifndef EASYICECONFIG_PROXIES__HPP
#define EASYICECONFIG_PROXIES__HPP

#include <Ice/Communicator.h>
#include <Ice/Ice.h>
#include <IceUtil/IceUtil.h>

namespace easyiceconfig {
namespace proxies{

template<typename T>
T
createProxy(const Ice::CommunicatorPtr &ic, const std::string proxyStr, bool stringIsAlreadyProxy){
    Ice::ObjectPrx base;

    if (stringIsAlreadyProxy){
        base = ic->stringToProxy(proxyStr); // Return: The proxy, or nil if str is an empty string.
    }else{
        base = ic->propertyToProxy(proxyStr); // Return: The proxy, or nil if property do not exist.
    }

    if (0 == base){
        throw Ice::ProxyParseException("easyiceconfig/proxy.hpp", 42, "Proxy arguments unmeet: passed configuration is empty.");
    }

    // unsafe (try-catch) to maintain original Exceptions
    T proxy = T::checkedCast(base);

    return proxy;
}

}} //NS

#endif // EASYICECONFIG_PROXIES__HPP

