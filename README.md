# libEasyIceConfig
***A library to tame Ice.Config***

## What provides?
This library is planned to simplify Ice.Config handle and add some useful features:
 * config files can be located in *any* place. [EasyIce]
 * simplify Ice Proxy creation and exception managenemt [EasyProxy]
 * port injection (not implemented)


## Expected usage
`#include <easyiceconfig/EasyIce.hpp>`
Then just replace:
  * **Ice::initialize**              ---> **EasyIce::initialize**
  * **Ice::createProperties** ---> **EasyIce::createProperties**


## EasyIce: load Ice.Config files from any place
Behavior:
```
Find Ice.Config filename into all defined search paths. Order is:
 * 1. current dir
 * 2. $ICE_CONFIG_PATH
 * 3. hardcored paths (.hpp)
```
Demostrative code:
```
#include <Ice/Ice.h>
#include <easyiceconfig/EasyIce.h>
#include <easyiceconfig/debug.hpp>
#include <iostream>

int main(int argc, char* argv[]){
    Ice::PropertiesPtr props = EasyIce::createProperties(argc, argv);
    easyiceconfig::debug::printProperties(props);
}
```

Console Output:
```
export ICE_CONFIG_PATH=/tmp:$ICE_CONFIG_PATH
$ ./test --Ice.Config=core.cfg,quadrotorplugin2.cfg,../conf/quadrotorplugin2.cfg,test.cfg
[Info] loaded Ice.Config file: /usr/local/share/jderobot/conf/core.cfg
[Info] loaded Ice.Config file: /tmp/quadrotorplugin2.cfg
[Info] loaded Ice.Config file: /usr/local/share/jderobot/conf/../conf/quadrotorplugin2.cfg
[Info] loaded Ice.Config file: test.cfg
Properties [0x973f70] has 8 entries:
	Ice.Config: ../conf/quadrotorplugin2.cfg,quadrotorplugin2.cfg,opencvdemo.cfg,test.cfg
	Opencvdemo.Camera.Proxy: cameraA:tcp -h 0.0.0.0 -p 9999
	Quadrotor.Adapter.Endpoints: default -h localhost -p 9000
	Quadrotor.CMDVel.Name: CMDVel
	Quadrotor.Camera.Name: Camera
	Quadrotor.Extra.Name: Extra
	Quadrotor.Navdata.Name: Navdata
	Quadrotor.Pose3D.Name: Pose3D
```

Here you are a very complex example:
 1. load core.cfg from predefined system path (/usr/local/share/jderobot/conf/)
 2. define testing search locations through $ICE_CONFIG_PATH
 3. relative paths works always, so you can even load hidden files by prepend path (quadrotorplugin2.cfg vs ../conf)
 4. forget everything and just use $PWD and retative paths (test.cfg)


## EasyProxy: simplify Proxy creation
EasyProxy simplifies Ice Proxy creation and exception managenemt.
It handles exceptions to provide a simple if scoped logic.
On error, original exception is retained allowing printing and throwing.

There are two ways to use this helper:

1. Full featured mode:
 * learn by example: [sensors.cpp & sensors.h](https://github.com/jderobot-varribas/JdeRobot/commit/b2d0abfa71aa4aaa45890125c5b9880e22fc4655#diff-a33e07f51a138184d6a927420d4fdb66)
 * No more explicit exception handling.
 * External usage remains unchanged (proxy pattern).
```
    EasyProxy<ClassPrx> proxy(ic,"X.Proxy", false)
    if (proxy)
        // do stuff
    else
        std::cout<<proxy.exception()
```
 
2. Fallback mode:
 * learn by example: [actuators.cpp](https://github.com/jderobot-varribas/JdeRobot/commit/b2d0abfa71aa4aaa45890125c5b9880e22fc4655#diff-88d009e3423e6a15579b833a847c0009)
 * It only requires changes at cpp
 * API (header) is unchanged.
```
    try {
     ClassPrx prx = easyiceconfig::proxies::createProxy<ClassPrx>(ic, "X.Proxy", false);
    }catch (Ice::Exception& e){
```

Basic walk-through: [test_proxy.cpp]( https://github.com/jderobot-varribas/libeasyiceconfig/blob/0.9.3.1/src/tests/test_proxy.cpp)


