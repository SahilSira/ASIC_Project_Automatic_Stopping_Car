# ASIC_Project_Automatic_Stopping_Car

This github repository summarizes the progress made in the ASIC class for the riscv_project.

# Aim of the project
The aim of the project is to design an automatic stopping car utilizing a specialized RISCV processor for obstacle detction, with the objective that a collision can be prevented without manual interaction.

# Working
A transmitter and an ultrasonic sensor is employed at the front of the car to detect the obstacle. Upon activating the transmitter an unltrasonic wave will transmit. Upon detection, the Motors will stop running to stop the car.

# Circuit Diagram
The following is not the final circuit but just for reference

![ckt](https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/3b4011e2-d583-4a79-a6a1-7685c417ff78)



# Block Diagram

![stopping car](https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/8a01e8f8-663b-4c99-b273-e68f0ce61047)

# C code
```bash


int trigger;
int echo;
int Motor1 = 1;
int Motor2 = 1;
int pulse_counter = 0;
int switch_val;

void read();
void pulse_count();
void distance_calc();
void trigger_send();
void delay_10us();
void delay_100ms();
void delay_200ms();
void stop();
void move_forward();

int main() {
    int motor1_reg, motor2_reg;

    // Calculate the motor control values
    motor1_reg = Motor1 * 4;
    motor2_reg = Motor2 * 4;

    // Use inline assembly to control motors
    asm volatile (
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        : "=r"(motor1_reg), "=r"(motor2_reg)
    );

    while (1) {
        read();
    }
    return 0;
}

void read() {
    asm volatile (
        "andi %0, x30, 1\n\t"
        : "=r"(switch_val)
    );
    if (switch_val) {
        pulse_count();
        pulse_counter = 0;
        delay_100ms();
    }
}

void pulse_count() {
    trigger_send();
    asm volatile (
        "andi %0, x30, 2\n\t"
        : "=r"(echo)
    );
    while (echo) {
        pulse_counter = pulse_counter + 1;
    }
    distance_calc();
}

void trigger_send() {
    int trigger_reg;
    trigger = 1;
    trigger_reg = trigger * 8;
    asm volatile (
        "or x30, x30, %0\n\t"
        : "=r"(switch_val)
    );
    delay_10us();
    trigger = 0;
    trigger_reg = trigger * 8;
    asm volatile (
        "or x30, x30, %0\n\t"
        : "=r"(switch_val)
    );
}

void distance_calc() {
    int distance;
    distance = pulse_counter * 172;
    if (distance <= 15) {
        stop();
        delay_200ms();
    } else {
        move_forward();
    }
}

void move_forward() {
    int motor1_reg, motor2_reg;

    // Set motor1 and motor2 to 1 to start them
    Motor1 = 1;
    Motor2 = 1;

    // Calculate the motor control values
    motor1_reg = Motor1 * 4;
    motor2_reg = Motor2 * 4;

    // Use inline assembly to control motors
    asm volatile (
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        : "=r"(motor1_reg), "=r"(motor2_reg)
    );
}

void stop() {
    int motor1_reg, motor2_reg;

    // Set motor1 and motor2 to 0 to stop them
    Motor1 = 0;
    Motor2 = 0;

    // Calculate the motor control values
    motor1_reg = Motor1 * 4;
    motor2_reg = Motor2 * 4;

    // Use inline assembly to control motors
    asm volatile (
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        : "=r"(motor1_reg), "=r"(motor2_reg)
    );
}

void delay_10us() {
    for (int i = 0; i < 10; i++);
}

void delay_100ms() {
    for (int i = 0; i < 100000; i++);
}

void delay_200ms() {
    for (int i = 0; i < 200000; i++);
}

```
# Assembly Code
```bash

out:     file format elf32-littleriscv


Disassembly of section .text:



```

# Unique Instructions
```bash
Number of different instructions: 17
List of unique instructions:
sll
bnez
jal
bge
nop
ret
or
mv
beqz
lui
sw
li
add
j
sub
and
lw

```
