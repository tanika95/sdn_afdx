Для сборки приложения понадобятся исходники NOX.
Установка в соответствии с туториалом:
https://github.com/CPqD/ofsoftswitch13/wiki/OpenFlow-1.3-Tutorial

А именно:

git clone git://github.com/mininet/mininet
mininet/util/install.sh -n3fxw

У меня возникли сложности с nox, устраняемые вот так:
cd nox
./boot.sh
cd build
../configure --with-boost-filesystem=boost_filesystem --with-boost-unit-test-framework=boost_unit_test_framework --with-boost-system=boost_system
make

Само приложение необходимо поместить в nox13oflib/src/nox/coreapps/
Скрипт conf.sh в nox13oflib

Сборка приложения:
./conf.sh

Запуск прижения:
./nox_core -v -i ptcp:6653 netcontrol

Прилежение имеет смысл запускать в совокупностью с эмулятором сети:
sudo mn --custom /<путь к сценарию>/3triangle.py --topo mytopo --mac --switch user --controller remote

3triangle.py находится в исходниках /testing/topos

В /testing/netc.xml содержится пример докумета, содержащего описание сети и потоков данных
В Netcontrol::scenario() находится пример сценария для разрыва линка между s1 и s2
