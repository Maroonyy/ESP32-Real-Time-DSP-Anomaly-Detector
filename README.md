# ESP32 Real-Time DSP Anomaly Detector

An ultra-low-latency, bare-metal Digital Signal Processing (DSP) pipeline built in C for the ESP32. This project processes raw, noisy analog sensor data in real-time to detect physical anomalies, circumventing the need for high-level ML libraries by relying strictly on discrete mathematical filters and manual memory management.

## 🧠 Core Engineering Architecture

This system acts as a real-time vibration/anomaly monitor, built using textbook Signals and Systems principles translated directly into hardware-safe C code:

* **Dynamic Circular Buffers (Pointer Arithmetic):** Implemented a constant-time $O(1)$ circular buffer using `malloc()` and raw pointer manipulation to manage a sliding window of sensor data without risking heap fragmentation or triggering memory leaks.
* **Z-Transform IIR Low-Pass Filter:** Translated a continuous-time transfer function into a discrete difference equation. The filter smooths high-frequency hardware noise in real-time using historical state memory (`static` variables in C).
    * $y[n] = 0.5 \cdot x[n] + 0.5 \cdot x[n-1]$
* **Discrete Signal Power Accumulator:** Continuously calculates the kinetic energy of the physical system by tracking the moving average of the squared signal amplitude. 
    * $P = \frac{1}{N} \sum_{i=0}^{N-1} (y[i])^2$
* **Hardware-Level Anomaly Triggers:** If the calculated power vector breaches the predefined catastrophic threshold, the C logic interrupts the serial flow to trigger an immediate system alarm.

## ⚙️ Hardware Integration

* **Microcontroller:** ESP32 (simulated via Wokwi)
* **Input Channel:** 12-bit ADC (Analog-to-Digital Converter) on Pin 34
* **Sensor:** Analog Potentiometer (simulating high-frequency mechanical vibration data)

## 🚀 Live Simulation

You do not need to compile this locally to see it run. You can test the memory management and DSP filtering live in the browser:

**[🔗 Click Here to Run the Live Wokwi Simulation]** *(Note: Paste your Wokwi project link here!)*

**To test the anomaly detector:**
1. Start the simulation.
2. Open the **Serial Plotter** to watch the C code actively filter the noisy signal from the clean signal.
3. Rapidly twist the potentiometer dial to maximum to simulate a catastrophic hardware failure. The system will detect the power spike and trigger the serial alarm.

## 📂 Repository Structure

* `sketch.ino` - The primary hardware configuration and infinite loop execution.
* `filter.h` - The custom DSP math library housing the memory structures, IIR filter, and power accumulator.
* `diagram.json` - The physical hardware routing for the ESP32 simulator.
