# Data Acquisition System (RTOS-Based)

This project implements a **Real-Time Data Acquisition System** using **ARM7 (LPC2129)** and **RTX RTOS**.  
The system samples analog data from sensors via ADC, processes it using multitasking under RTOS, and displays values on an LCD.

## 🚀 Features
- Real-time multitasking using RTX RTOS
- Periodic ADC sampling and task scheduling
- RTC-based time stamping
- LCD display of acquired sensor data
- UART data transmission for PC monitoring

## 🧩 Hardware Used
- ARM7 LPC2129 Microcontroller  
- LCD 16x2 Display  
- LM35 Temperature Sensor  
- RTC (DS1307) via I2C  
- UART (for serial monitoring)

## ⚙️ Software
- Keil µVision / GCC ARM toolchain  
- Proteus simulation for verification  
- Real-time debugging with RTX RTOS

## 📂 Project Structure
- `src/` – Source files (drivers, RTOS tasks)
- `inc/` – Header files
- `Makefile` – Build automation (for GCC)
- `README.md` – Project documentation

## 📸 Output Preview

### LCD Display Output
![LCD Output](https://github.com/prathameshsalunkhe/Data-Acquisition-System-RTOS/blob/main/image/data_acq.jpg)

### Proteus Simulation
![Proteus Simulation](https://github.com/prathameshsalunkhe/Data-Acquisition-System-RTOS/blob/main/image/protuse.png)


## 📬 Author
**Prathamesh Salunkhe**  
Embedded Engineer | Real-Time Systems Enthusiast  
[LinkedIn](https://www.linkedin.com/in/prathamesh-embedded/) | [Email](mailto:pssalunkhe5@gmail.com)
