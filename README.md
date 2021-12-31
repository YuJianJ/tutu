# tutu
基于乐鑫ESP开发的遥控系统，包括车辆控制、图传功能等，用于分析常用协议、实践外设移植，仅供学习。

# 开源地址
https://github.com/YuJianJ/tutu.git

# 环境安装
## 硬件
- 履带平台
- ESP32 、 ESP32-cam等核心板
- 370直流电机
- L298N
- MPU6050
## 软件
- VScode (Windows/MacOS/Ubuntu)
- PlatformIO
- ESP-idf
- ESP-arduino
- Blinker-lib

# 协议及外设
## iic
- MPU6050  // 三维角度传感器用于修正车辆角度、设备角度、速度等
## wifi
- Blinker  // 基于Blinker的库建立了一个wifi传输系统
## ble
## uwb
## uart
- 串口  // 串口传输
