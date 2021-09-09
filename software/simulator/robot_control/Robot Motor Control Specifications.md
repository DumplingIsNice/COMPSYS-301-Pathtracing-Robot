# Robot Motor Control Specifications
**Aim:** This file documents the code structure and function header of components
that dictates the robot motor control.

## Assumptions:
### "Perfect Motion"
In reality, the robot may be misaligned do to in precision in speed, direction etc.
This requires **calibration** capabilities for when the robot deviates from the
**expected position**.

Effectively, there will be several **finite, discrete positional states** the robot may be in (even while travelling).
Meanwhile in reality, the robot is in **infinite, continuum of states** which aim to match the discrete positional states.

> **i.e.** We expect robot to be aligned with the path running through its mid points, but this may not be true *if*: 
> - When entering this position, there are errors in physical motion.

In the first stages of design in the simulator, we must design our movement functions
to move precisely for us to assume perfect motion.

### Static, Determined Path
The **expected path of travel** is pre-computed by path-finding algorithms via the `map.h` map information. The robot simply need to:

- Carry out the expected path.
  - Know its progress along this path. 

### Controller
The motor control should be encapsulated into a series of actuation functions which the controller may call up to move the robot, as if the robot's motion is dictated by a controller. 

### Global Variables

TBD - We need to determine the necessary global variables.

## Actuation

```c
// Commands
void robo_forward_const(); // Move robot forward at constant speed.
void robo_turn(); // Turns robot on a dime.
void robo_stop(); // Stops robot motion after the current commands have completed.
void robo_halt(); // Strong abort ALL motor commands. 

// Settings
void set_speed(speed);
void set_angular_speed(ang_speed);
/* 
Func also determine the dir of robo_turn() tt. respect to the robot's facing.
    - -ve, turn left.
    - +ve, turn right.
    - 0, no turn.
*/
void set_turn_angle(turn_angle); 
```

## Sensors & Controller

### Sensor
```c
void sensor_handler(sensor_information, calc_path, control_signal);
/* 
    This function will handle the returned sensor signals (array) 
    and compute the necessary control signals for the motion control logic.
*/ 
```

### Controller
```c
void recognize_progress();
void log_progress();
/* 
    This pair of functions will recognize the progress the robot has made along its expected path. 
    Then also update the linked-list of its progress.
*/ 
```
