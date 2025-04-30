


# 🕹️ Differential Wheeled Robot Control via PS3 Controller

*Wireless control of differential wheeled robot using PS3 Bluetooth controller with ESP32*

---

## 📌 Project Overview
This project combines:
1. **PS3 Bluetooth Control** - Wireless communication between PS3 controller and ESP32
2. **STM32 Firmware Hack** - Modified hoverboard motherboard firmware for custom motor control
3. **Safety System** - Automatic stop on controller disconnect

---

## 🔧 Firmware Hierarchy
| Component               | Role                          | Source |
|-------------------------|-------------------------------|--------|
| **PS3 Controller Layer**| Handles Bluetooth communication | [PS3-ESP32](https://github.com/jvpernis/esp32-ps3) |
| **STM32 Hack**          | Motor control logic           | [Hoverboard-Firmware-Hack](https://github.com/EmanuelFeru/hoverboard-firmware-hack) |

---

## 🚀 Key Features
- **Bluetooth Control**
  - Latency: <20ms
  - Range: Up to 10m
  - Auto-stop safety: Halts motors on controller disconnect
- **STM32 Modifications**
  - Custom speed/acceleration profiles
  - Deadband filtering
  - Safety cutoffs
  - Analog stick calibration support

---

## ⚙️ Firmware Setup
### 1. STM32 Hoverboard Firmware
**Source**: [hoverboard-firmware-hack-FOC](https://github.com/hoverboard-robotics/hoverboard-firmware-hack-FOC/tree/master)  
**Modified Files**:
```
firmware_mods/
├── main.c               # Motor control logic
├── config.h             # Critical parameters
└── platformio.ini              
```

**Flashing Steps**:
1. Connect ST-Link V2 to hoverboard mainboard
2. Use STM32CubeProgrammer:

*Full guide: [Original Instructions](https://github.com/hoverboard-robotics/hoverboard-firmware-hack-FOC/tree/master)*

---

## 🎮 PS3 Controller Setup
### Pairing Procedure
1. Upload ESP32 controller code with PS3 MAC address
2. Put PS3 controller in pairing mode (PS button)
3. ESP32 automatically connects when powered
4. Solid LED = Connected, Blinking LED = Searching

**Safety Feature**: Motors immediately stop if connection drops

---

## 🛠️ Hardware Setup
| Component               | Quantity | Notes |
|-------------------------|----------|-------|
| Hoverboard Motherboard  | 1        | STM32F103 based |
| ESP32                   | 1        | Bluetooth enabled |
| PS3 Controller          | 1        | DualShock 3 compatible |
| ST-Link Programmer      | 1        | For STM32 flashing |
| 36V Battery             | 1        | Hoverboard main power |

**Wiring**:
```mermaid
graph LR
  PS3_Controller -->|Bluetooth| ESP32
  ESP32 -->|DAC| STM32
  STM32 -->|PWM| Motor_Driver
```

---

## ⚠️ Critical Notes
1. **Connection Safety**:
   - Robot automatically stops if:
     - Controller battery low
     - Bluetooth signal lost 
     - Emergency stop button pressed
2. Configuration Parameters:
```cpp
// esp32_controller.ino
#define acc 50   //acceleration step if you don't need acceleration and dceleration you can make it equal to maxspeed
#define accDelay 250 //acceleration delay
#define maxspeed 100 // max value frome the center (between 0 and 126)
#define deadband 5     // Ignore stick drift

```

3. Motor Control Logic (STM32):
```cpp
// main.c modifications
steer *= 0.12;  // PS3 analog stick scaling
speed *= 0.12;  // Adjust for sensitivity
```

---

## 📜 License & Attribution
- **STM32 Firmware**: [hoverboard-firmware-hack-FOC](https://github.com/hoverboard-robotics/hoverboard-firmware-hack-FOC/tree/master) (GPLv3)

- **Modifications**: [achref-ak](https://github.com/your-repo/hoverboard-wireless)

---

## 🔒 Safety Implementation
The ESP32 continuously monitors controller connection status:

Motors remain disabled until controller reconnects
