# Can a temperature chamber be made using heat lamps?

These heating lamps, for the use in which I discovered them, are used to dry automotive paint on different surfaces. However if we want to control this temperature we need to control the intensity of the lamp. However these lamps work directly connected to the AC signal and to control the intensity of these we need to control the input signal by applying phase control techniques.

## First approach - Prototype

The circuit includes an opto-isolated zero-crossing detector and a trigger circuit for the TRIAC. Opto-isolators are crucial for separating low voltage signals from high-power circuits, ensuring safety.

The zero-crossing detection generates pulses that the Arduino uses to trigger the TRIAC at the right moments. When a zero-crossing is detected, the TRIAC remains off for a set time (t1), reducing the power supplied to the AC load. After this time, the Arduino turns on the TRIAC by applying voltage to its gate. Once activated, the TRIAC stays on until the AC signal crosses zero again.

The duration of the gate pulse (t2) is essential—if it’s too short, the TRIAC won't trigger. By chopping parts of the AC waveform, we effectively control the power delivered, similar to Pulse Width Modulation (PWM) but for AC signals.

![image](https://github.com/user-attachments/assets/e4be1e3d-4dd4-41e4-b73d-1e7cd7dce539)
* Ref: AC phase control - Arduino playground

![image](https://github.com/user-attachments/assets/e9000cc4-aaa6-4c2d-8d90-78595d7df12d)
* Ref: O. Pinzon-Ardila

As a first result. using this circuit we can control AC phase for dimmer the intensity of light. *check attach video for more info.*


## Second approach - Created

In this part, we decided to move the components from a breadboard to a PCB, create the mechanical structure and add some temperature sensors in order to apply a closed-loop control system.

### PCB design
![image](https://github.com/user-attachments/assets/dcb2cd50-2aa9-4c01-8cc6-625796464af4)
![image](https://github.com/user-attachments/assets/7c212a73-d338-497a-8873-dd89cae61372)

### Mechanical structure
![image](https://github.com/user-attachments/assets/15b185c5-5b2d-4f69-9ab1-6b75e1870d94)

### Actuators
The actuators used were heating lamps located at the top of the chamber. Type K thermocouples were used as sensors.

![07bd02fb-d253-4346-b17c-7e07df27a975](https://github.com/user-attachments/assets/1d63cb06-ba64-4450-87b7-73215a78bc54)


## Third approach - Control
![image](https://github.com/user-attachments/assets/9290fc3a-a1c0-49a9-80b2-5a02b81ab517)

![image](https://github.com/user-attachments/assets/dd1e3127-29b0-4ecb-abb2-e7c086e3ea49)

The Ziegler-Nichols methodology for control loop design is a widely used technique for tuning the parameters of a PID (Proportional, Integral, Derivative) controller. This methodology is based on an empirical approach and seeks to find suitable values for the controller through testing and tuning.

After validating the system in open loop, the control parameters were implemented in an existing Arduino library.



