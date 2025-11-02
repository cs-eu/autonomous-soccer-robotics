# Autonomous Soccer Robot

An autonomous, competition-ready soccer robot designed and built for a educational robotics competition.

---

## Overview

The **Autonomous Soccer Robot** was engineered to:

* Detect and track a ball using 360° vision
* Navigate the field holonomically in any direction
* Handle and shoot the ball autonomously
* Operate completely untethered under RoboCupJunior Soccer rules

Every part — from the **mechanical design** and **custom PCBs** to the **embedded firmware** and **computer vision** algorithms — was developed by our team.

This repository provides a complete, open-source reference for educational and research use.

---

## Project Structure

```
.
├── docs/                # Documentation and reference material
│   ├── electronics/     # Schematics, PCB layouts, and Eagle files
│   ├── hardware/        # CAD designs, drawings, and mechanical notes
│   └── parts-lists/     # Component, ordering, and assembly lists
│
├── firmware/            # Embedded control software (C/C++ / PlatformIO)
│   ├── calibration-tools/  # Sensor calibration and testing utilities
│   ├── main-controller/    # High-level control (movement, PID, logic)
│   ├── sensor-node/        # Sensor acquisition and preprocessing
│   └── tests/              # Unit and integration tests
│
├── libraries/           # Shared hardware abstraction and logic libraries
│   ├── Bodensensoren/   # Floor sensor modules
│   ├── IMU/             # IMU driver and orientation estimation
│   ├── TOF/             # Time-of-Flight distance sensing
│   ├── Motors/          # Motor control and PID regulation
│   ├── TACTICS/         # Robot state machine and strategy modules
│   └── ...              # Additional hardware interface libraries
│
├── mechanical/          # Physical design and fabrication files
│   ├── 3d-models/       # Fusion 360 models and 3D-print files (.stl, .f3d)
│   ├── eagle-pcb/       # Custom PCB layouts and Eagle libraries
│   └── metal-fabrication/ # CNC drawings, step files, and laser-cut designs
│
└── vision/              # Computer vision and image processing
    ├── docker/          # Dockerfiles for OpenCV build environments
    └── tinkerboard/     # Tinker Board vision software (Python + OpenCV)
```

---

## System Architecture

### Hardware Overview

* **Drive System:** Three-wheel omnidirectional base (holonomic drive)
* **Dribbler:** DC-motor-driven adhesive roller for ball handling
* **Kicker:** Solenoid-based shooting mechanism powered via capacitor buffer
* **Main Controller:** Dual **Teensy 3.6** microcontrollers for control & sensing
* **Vision Processor:** **ASUS Tinker Board** running OpenCV (Python)
* **Sensors:**

  * Raspberry Pi camera + parabolic mirror (360° vision)
  * 4× Time-of-Flight (ToF) distance sensors
  * 32× photoresistor array with RGB illumination for boundary detection

---

## Software Overview

| Layer             | Platform                     | Language                  | Description                                           |
| ----------------- | ---------------------------- | ------------------------- | ----------------------------------------------------- |
| **Vision**        | Tinker Board (SBC)           | Python + OpenCV           | Detects the ball and extracts angular bearing         |
| **Control**       | Teensy 3.6                   | C/C++ (Arduino Framework) | Motion control, PID regulation, actuator management   |
| **Communication** | Serial protocol (custom CRC) | C/Python                  | Reliable low-latency data exchange (<20 ms loop time) |

### Control Loop

The control system computes translational and rotational velocities from sensor inputs, applying:
[
u(t) = K_p e(t) + K_i \int e(t),dt + K_d \frac{de(t)}{dt}
]
Each wheel’s speed is regulated through independent PID loops for smooth, responsive motion.

---

## Mechanical Design

The chassis combines **CNC-milled aluminum** for structural integrity with **3D-printed polymer shells** for lightweight coverage and modular maintenance.
All components were modeled in **Autodesk Fusion 360**, allowing precise alignment and rapid iteration.

---

## Electronics

* **Custom PCBs** for motor drivers, solenoid control, and power regulation
* Designed using **Autodesk Eagle**
* Multiple voltage rails (12V / 5V / 3.3V) with overcurrent and thermal protection
* Modular connectors for fast servicing during competition

---

## Vision and Perception

The 360° vision system uses a **catadioptric setup** (camera + parabolic mirror) to obtain a full panoramic field view.
Processing steps include:

1. Image unwarping to cylindrical projection
2. Color filtering to detect the orange ball
3. Contour and centroid extraction
4. Angular position estimation relative to robot center

Additional data from ToF sensors and photoresistors provide:

* Boundary line detection
* Obstacle proximity sensing
* Position estimation support

