
Инструкции по подключению RFID модуля RC522 и шагового мотора BYJ48 к роботу turtlebro.  

Важно:  
Шаговый мотор мы подключаем к ардуино через драйвер uln2003, а RFID модуль - напрямую к GPIO-пинам Raspberry.  

----------------------------------------------------------------------------------------------

А. Подключение шагового мотора  

[Примеры подключения и работы с шаговым мотором]( http://robotosha.ru/arduino/stepper-motor-28byj-uln2003-arduino.html)  
[Документация на драйвер ULN2003](https://rudatasheet.ru/datasheets/uln2003/)  
[Еще пример подключения шагового мотора BYJ48](https://www.instructables.com/id/BYJ48-Stepper-Motor/)  

Стандартная библиотека Stepper не умеет по умолчанию работать с моторами BYJ48, поэтому надо использовать библиотеку AccelStepper.  
Исходный код [здесь](https://github.com/d235j/AccelStepper/)  
Вы можете найти ее в менеджере библиотек Arduino IDE  
Простой пример работы с этой библиотекой, взятый по одной из приложенных выше ссылок:  

```
#include<Arduino.h>
#include<AccelStepper.h>
 
#define HALFSTEP 8   

// Определение пинов для управления двигателем
#define motorPin1  8 // IN1 на 1-м драйвере ULN2003
#define motorPin2  9 // IN2 на 1-м драйвере ULN2003
#define motorPin3  10 // IN3 на 1-м драйвере ULN2003
#define motorPin4  11 // IN4 на 1-м драйвере ULN2003
 
// Инициализируемся с последовательностью выводов IN1-IN3-IN2-IN4 
// для использования AccelStepper с 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
 
void setup(){
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(10.0);
  stepper1.setSpeed(100);
  stepper1.moveTo(2048);
}
 
void loop(){
  // Изменяем направление, если шаговик достигает заданного положения
  if(stepper1.distanceToGo()==0)
    stepper1.moveTo(-stepper1.currentPosition());
  stepper1.run();
}
```

------------------------------------------------------------------------------

Б. Подключение RFID модуля  

Для работы с модулем RFID RC522 мы должны использовать библиотеку MFRC522-python, ее придется скачать и установить на Raspberry.  
Исходный код [здесь](https://github.com/mxgxw/MFRC522-python)  
По умолчанию она работает с питоном-2.7, поэтому нам будет легко использовать ее вместе с ros-melodic.  
Для работы с модулем  RFID нужно подключить его к SPI-пинам RPi, а также загрузить библиотеку SPI 
Исходный код [здесь](https://github.com/lthiery/SPI-Py)  

Чтобы сделать все это нужно проделать следующие шаги:  

0. Подключите модуль RFID RC522 к тем пинам RPi, которые указаны в инструкции в самой [библиотеке](https://github.com/mxgxw/MFRC522-python)     
Чтобы не запутаться, нужно пользоваться документацией с [сайта разработчикой](https://www.raspberrypi.org/documentation/usage/gpio/)  
Будьте внимательны при подключении, запутаться очень легко.  

1. Включить SPI на Raspberry  

```
sudo raspi-config
```

Затем выбрать среди меню интерфейсов SPI и выбрать "enable".  

2. Перезапустить Raspberry чтобы активировать spi   

```
sudo reboot
```

3. Проверить, что устройство spi_bcm2835 в списке подключенных  

```
lsmod | grep spi  
```

4. Скачать git репозиторий библиотеки SPI-Py, перейти в его директорию  

```
git clone https://github.com/lthiery/SPI-Py.git
cd SPI-Py
```

5. Откатить репозиторий SPI-Py к версии, совместимой с нашей системой, и установить  
(подробнее https://github.com/mxgxw/MFRC522-python/issues/69#issuecomment-466023799)  

```
git checkout 8cce26b9ee6e69eb041e9d5665944b88688fca68
sudo python setup.py install
cd ..
```

6. Скачать репозиторий библиотеки MFRC522-python, перейти в его директорию   

```
git clone https://github.com/mxgxw/MFRC522-python.git
cd MFRC522-python
```

7. Запустить тестовый скрипт, который читает содержимое одного блока памяти RFID-карты  

```
python Read.py
```

8. Запустить тестовый скрипт, который читает все содержимое одного памяти RFID-карты  

```
python Dump.py
```

9. Запустить тестовый скрипт, который записывает 16 байтов в один блок памяти RFID-карты  

```
python Write.py
```
