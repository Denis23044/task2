# task2
Возникла ошибка при компилляции. Не могу понять, в чем проблема. Пробовал перезагрузить среду, откатить до дефолт настроек. Не помогло
Выдает это:
====================[ Build | task2 | Debug ]===================================
"D:\CLion\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" --build "D:\Учебная литература\Информатика\Сорокоумов\task2\cmake-build-debug" --target task2
[1/2] Building CXX object CMakeFiles/task2.dir/Device.cpp.obj
FAILED: CMakeFiles/task2.dir/Device.cpp.obj 
"D:\CLion\CLion 2021.3.3\bin\mingw\bin\g++.exe"   -g -std=gnu++14 -MD -MT CMakeFiles/task2.dir/Device.cpp.obj -MF CMakeFiles\task2.dir\Device.cpp.obj.d -o CMakeFiles/task2.dir/Device.cpp.obj -c "D:/Учебная литература/Информатика/Сорокоумов/task2/Device.cpp"
In file included from D:/Учебная литература/Информатика/Сорокоумов/task2/Device.h:9,
                 from D:/Учебная литература/Информатика/Сорокоумов/task2/Device.cpp:5:
D:/Учебная литература/Информатика/Сорокоумов/task2/Contact.h:17:5: error: 'Device' does not name a type
   17 |     Device *device;
      |     ^~~~~~
D:/Учебная литература/Информатика/Сорокоумов/task2/Contact.h:19:76: error: 'Device' has not been declared
   19 |     explicit Contact(int x=0, int y=0, int contact_num=0, int plate_num=0, Device *device=nullptr);
      |                                                                            ^~~~~~
D:/Учебная литература/Информатика/Сорокоумов/task2/Contact.h:24:5: error: 'Device' does not name a type
   24 |     Device *getDevice();
      |     ^~~~~~
ninja: build stopped: subcommand failed.
