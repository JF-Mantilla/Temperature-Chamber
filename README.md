# Can a temperature chamber be made using heat lamps?

These heating lamps, for the use in which I discovered them, are used to dry automotive paint on different surfaces. However if we want to control this temperature we need to control the intensity of the lamp. However these lamps work directly connected to the AC signal and to control the intensity of these we need to control the input signal by applying phase control techniques.

## First approach

The circuit includes an opto-isolated zero-crossing detector and a trigger circuit for the TRIAC. Opto-isolators are crucial for separating low voltage signals from high-power circuits, ensuring safety.

The zero-crossing detection generates pulses that the Arduino uses to trigger the TRIAC at the right moments. When a zero-crossing is detected, the TRIAC remains off for a set time (t1), reducing the power supplied to the AC load. After this time, the Arduino turns on the TRIAC by applying voltage to its gate. Once activated, the TRIAC stays on until the AC signal crosses zero again.

The duration of the gate pulse (t2) is essential—if it’s too short, the TRIAC won't trigger. By chopping parts of the AC waveform, we effectively control the power delivered, similar to Pulse Width Modulation (PWM) but for AC signals.

![image](https://github.com/user-attachments/assets/e4be1e3d-4dd4-41e4-b73d-1e7cd7dce539)
Ref: AC phase control - Arduino playground

![image](https://github.com/user-attachments/assets/e9000cc4-aaa6-4c2d-8d90-78595d7df12d)
Ref: O. Pinzon-Ardila
