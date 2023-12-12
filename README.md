# Automatic_Stopping_Car

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


#include <stdio.h>
#include <stdlib.h>
int main() 
  {
    int Motor1 = 1;
    int Motor2 = 1;
    int pulse_counter = 0;
    int switch_val;
    int motor1_reg, motor2_reg;
    int trigger = 0;
    int echo;
    int distance;
    int trigger_reg;
    int i;
    int mask1= 0xFFFFFFE3;
    
while (1) 
     {
        // Calculate the motor control values
        motor1_reg = Motor1 * 4;
        motor2_reg = Motor2 * 8;
        // Use inline assembly to control motors
        asm volatile (
            "and x30, x30, %2\n\t"
            "or x30, x30, %0\n\t"
            "or x30, x30, %1\n\t"
            :
            : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
            : "x30"
            );

        // Read switch_val
        asm volatile (
            "andi %0, x30, 1\n\t"
            : "=r"(switch_val)
            );
        switch_val=1;
        if (switch_val) 
          {
            // Send trigger
            trigger = 1;
            trigger_reg = trigger * 16;
            asm volatile (
                "and x30, x30, %1\n\t"
                "or x30, x30, %0\n\t"
                :
                : "r"(trigger_reg), "r"(mask1)
                :"x30"
                );

            // Delay 10 microseconds
            for (int i = 0; i < 10; i++);

            trigger = 0;
            trigger_reg = trigger * 16;
            asm volatile (
                "and x30, x30, %1\n\t"
                "or x30, x30, %0\n\t"
                :
                : "r"(trigger_reg), "r"(mask1)
                :"x30"
                );



          
            // Read echo
          
            asm volatile (
                "andi %0, x30, 2\n\t"
                : "=r"(echo)
                );

          
            
            if (echo) 
              {
                pulse_counter = pulse_counter + 1;
              }
            

            // Calculate distance
              else
		{ 
 
		distance = pulse_counter * 172;
                

                if (distance <=20000 ) 
                  {
                    
                    // Stop motors
                    Motor1 = 0;
                    Motor2 = 0;
                
                // Calculate the motor control values
                    motor1_reg = Motor1 * 4;
                    motor2_reg = Motor2 * 8;

                // Use inline assembly to control motors
                    asm volatile (
                        "and x30, x30, %2\n\t"
                        "or x30, x30, %0\n\t"
                        "or x30, x30, %1\n\t"
                        :
                        : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
                        : "x30"
                        );



                    // Delay 200 milliseconds
                    for (int i = 0; i < 200000; i++);
                  } 
                  
                  else 
                    {
                      // Start motors
                      
                      Motor1 = 1;
                      Motor2 = 1;

                      // Calculate the motor control values
                      motor1_reg = Motor1 * 4;
                      motor2_reg = Motor2 * 8;

                      
                      // Use inline assembly to control motors
                    asm volatile (
                        "and x30, x30, %2\n\t"
                        "or x30, x30, %0\n\t"
                        "or x30, x30, %1\n\t"
                        :
                        : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
                        : "x30"
                        );

          
                    }
                  
              
        	}
        }
 
    }
    return 0;
}


```
# Assembly Code
```bash



out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fb010113          	addi	sp,sp,-80
   10058:	04812623          	sw	s0,76(sp)
   1005c:	05010413          	addi	s0,sp,80
   10060:	00100793          	li	a5,1
   10064:	fef42623          	sw	a5,-20(s0)
   10068:	00100793          	li	a5,1
   1006c:	fef42423          	sw	a5,-24(s0)
   10070:	fe042223          	sw	zero,-28(s0)
   10074:	fc042c23          	sw	zero,-40(s0)
   10078:	fe300793          	li	a5,-29
   1007c:	fcf42a23          	sw	a5,-44(s0)
   10080:	fec42783          	lw	a5,-20(s0)
   10084:	00279793          	slli	a5,a5,0x2
   10088:	fcf42823          	sw	a5,-48(s0)
   1008c:	fe842783          	lw	a5,-24(s0)
   10090:	00379793          	slli	a5,a5,0x3
   10094:	fcf42623          	sw	a5,-52(s0)
   10098:	fd042783          	lw	a5,-48(s0)
   1009c:	fcc42703          	lw	a4,-52(s0)
   100a0:	fd442683          	lw	a3,-44(s0)
   100a4:	00df7f33          	and	t5,t5,a3
   100a8:	00ff6f33          	or	t5,t5,a5
   100ac:	00ef6f33          	or	t5,t5,a4
   100b0:	001f7793          	andi	a5,t5,1
   100b4:	fcf42423          	sw	a5,-56(s0)
   100b8:	00100793          	li	a5,1
   100bc:	fcf42423          	sw	a5,-56(s0)
   100c0:	fc842783          	lw	a5,-56(s0)
   100c4:	fa078ee3          	beqz	a5,10080 <main+0x2c>
   100c8:	00100793          	li	a5,1
   100cc:	fcf42c23          	sw	a5,-40(s0)
   100d0:	fd842783          	lw	a5,-40(s0)
   100d4:	00479793          	slli	a5,a5,0x4
   100d8:	fcf42223          	sw	a5,-60(s0)
   100dc:	fc442783          	lw	a5,-60(s0)
   100e0:	fd442703          	lw	a4,-44(s0)
   100e4:	00ef7f33          	and	t5,t5,a4
   100e8:	00ff6f33          	or	t5,t5,a5
   100ec:	fe042023          	sw	zero,-32(s0)
   100f0:	0100006f          	j	10100 <main+0xac>
   100f4:	fe042783          	lw	a5,-32(s0)
   100f8:	00178793          	addi	a5,a5,1
   100fc:	fef42023          	sw	a5,-32(s0)
   10100:	fe042703          	lw	a4,-32(s0)
   10104:	00900793          	li	a5,9
   10108:	fee7d6e3          	bge	a5,a4,100f4 <main+0xa0>
   1010c:	fc042c23          	sw	zero,-40(s0)
   10110:	fd842783          	lw	a5,-40(s0)
   10114:	00479793          	slli	a5,a5,0x4
   10118:	fcf42223          	sw	a5,-60(s0)
   1011c:	fc442783          	lw	a5,-60(s0)
   10120:	fd442703          	lw	a4,-44(s0)
   10124:	00ef7f33          	and	t5,t5,a4
   10128:	00ff6f33          	or	t5,t5,a5
   1012c:	002f7793          	andi	a5,t5,2
   10130:	fcf42023          	sw	a5,-64(s0)
   10134:	fc042783          	lw	a5,-64(s0)
   10138:	00078a63          	beqz	a5,1014c <main+0xf8>
   1013c:	fe442783          	lw	a5,-28(s0)
   10140:	00178793          	addi	a5,a5,1
   10144:	fef42223          	sw	a5,-28(s0)
   10148:	f39ff06f          	j	10080 <main+0x2c>
   1014c:	fe442703          	lw	a4,-28(s0)
   10150:	00070793          	mv	a5,a4
   10154:	00179793          	slli	a5,a5,0x1
   10158:	00e787b3          	add	a5,a5,a4
   1015c:	00279793          	slli	a5,a5,0x2
   10160:	40e787b3          	sub	a5,a5,a4
   10164:	00279793          	slli	a5,a5,0x2
   10168:	40e787b3          	sub	a5,a5,a4
   1016c:	00279793          	slli	a5,a5,0x2
   10170:	faf42e23          	sw	a5,-68(s0)
   10174:	fbc42703          	lw	a4,-68(s0)
   10178:	000057b7          	lui	a5,0x5
   1017c:	e2078793          	addi	a5,a5,-480 # 4e20 <main-0xb234>
   10180:	06e7c263          	blt	a5,a4,101e4 <main+0x190>
   10184:	fe042623          	sw	zero,-20(s0)
   10188:	fe042423          	sw	zero,-24(s0)
   1018c:	fec42783          	lw	a5,-20(s0)
   10190:	00279793          	slli	a5,a5,0x2
   10194:	fcf42823          	sw	a5,-48(s0)
   10198:	fe842783          	lw	a5,-24(s0)
   1019c:	00379793          	slli	a5,a5,0x3
   101a0:	fcf42623          	sw	a5,-52(s0)
   101a4:	fd042783          	lw	a5,-48(s0)
   101a8:	fcc42703          	lw	a4,-52(s0)
   101ac:	fd442683          	lw	a3,-44(s0)
   101b0:	00df7f33          	and	t5,t5,a3
   101b4:	00ff6f33          	or	t5,t5,a5
   101b8:	00ef6f33          	or	t5,t5,a4
   101bc:	fc042e23          	sw	zero,-36(s0)
   101c0:	0100006f          	j	101d0 <main+0x17c>
   101c4:	fdc42783          	lw	a5,-36(s0)
   101c8:	00178793          	addi	a5,a5,1
   101cc:	fcf42e23          	sw	a5,-36(s0)
   101d0:	fdc42703          	lw	a4,-36(s0)
   101d4:	000317b7          	lui	a5,0x31
   101d8:	d3f78793          	addi	a5,a5,-705 # 30d3f <__global_pointer$+0x1f317>
   101dc:	fee7d4e3          	bge	a5,a4,101c4 <main+0x170>
   101e0:	ea1ff06f          	j	10080 <main+0x2c>
   101e4:	00100793          	li	a5,1
   101e8:	fef42623          	sw	a5,-20(s0)
   101ec:	00100793          	li	a5,1
   101f0:	fef42423          	sw	a5,-24(s0)
   101f4:	fec42783          	lw	a5,-20(s0)
   101f8:	00279793          	slli	a5,a5,0x2
   101fc:	fcf42823          	sw	a5,-48(s0)
   10200:	fe842783          	lw	a5,-24(s0)
   10204:	00379793          	slli	a5,a5,0x3
   10208:	fcf42623          	sw	a5,-52(s0)
   1020c:	fd042783          	lw	a5,-48(s0)
   10210:	fcc42703          	lw	a4,-52(s0)
   10214:	fd442683          	lw	a3,-44(s0)
   10218:	00df7f33          	and	t5,t5,a3
   1021c:	00ff6f33          	or	t5,t5,a5
   10220:	00ef6f33          	or	t5,t5,a4
   10224:	e5dff06f          	j	10080 <main+0x2c>


```

# Unique Instructions
```bash
Number of different instructions: 16
List of unique instructions:
addi
beqz
lw
sub
j
lui
or
sw
andi
add
slli
bge
and
blt
li
mv



```

# Spike Simulation


- After this, we define the inputs and outputs using asm to link the assemply level inputs and outputs and store them over variables in C.

- **code for spike simulation**
```bash
#include <stdio.h>
#include <stdlib.h>
int main() 
  {
    int Motor1 = 1;
    int Motor2 = 1;
    int pulse_counter = 0;
    int switch_val;
    int motor1_reg, motor2_reg;
    int trigger = 0;
    int echo;
    int distance;
    int trigger_reg;
    int i;
    int mask1= 0xFFFFFFE3;
    
    distance = 21;//sahil
    for(i=0;i<3;i++)
    //while (1) 
     {
        // Calculate the motor control values
        motor1_reg = Motor1 * 4;
        motor2_reg = Motor2 * 8;
        // Use inline assembly to control motors
        asm volatile (
            "and x30, x30, %2\n\t"
            "or x30, x30, %0\n\t"
            "or x30, x30, %1\n\t"
            :
            : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
            : "x30"
            );
        printf("motor1_reg=%d\n",motor1_reg);//sahil
        printf("motor2_reg=%d\n",motor2_reg);//sahil
        printf("motor1=%d\n",Motor1);//sahil
        printf("motor2=%d\n",Motor2);//sahil
        // Read switch_val
        asm volatile (
            "andi %0, x30, 1\n\t"
            : "=r"(switch_val)
            );
        switch_val=1;
        if (switch_val) 
          {
            // Send trigger
            trigger = 1;
            trigger_reg = trigger * 16;
            asm volatile (
                "or x30, x30, %0\n\t"
                : "=r"(trigger_reg)
                );
            printf("switch_val=%d\n",switch_val);//sahil
            printf("trigger=%d\n",trigger);//sahil

            printf("trigger_reg=%d\n",trigger_reg);//sahil

            // Delay 10 microseconds
            for (int i = 0; i < 10; i++);

            trigger = 0;
            trigger_reg = trigger * 16;
            asm volatile (
                "and x30, x30, %1\n\t"
                "or x30, x30, %0\n\t"
                :
                : "r"(trigger_reg), "r"(mask1)
                :"x30"
                );
            printf("trigger_reg=%d\n",trigger_reg);//sahil
            printf("trigger=%d\n",trigger);//sahil


          
            // Read echo
          
            asm volatile (
                "andi %0, x30, 2\n\t"
                : "=r"(echo)
                );
            echo=1;//sahil
            printf("echo=%d\n",echo);//sahil
          
            
            while (echo) 
              {
                pulse_counter = pulse_counter + 1;
                echo=0;
              }
            

            // Calculate distance
                //distance = pulse_counter * 172;
                
                printf("distance=%d\n",distance);//sahil
                if (distance <=20 ) 
                  {
                    
                    // Stop motors
                    Motor1 = 0;
                    Motor2 = 0;
                
                // Calculate the motor control values
                    motor1_reg = Motor1 * 4;
                    motor2_reg = Motor2 * 8;

                // Use inline assembly to control motors
                    asm volatile (
                        "and x30, x30, %2\n\t"
                        "or x30, x30, %0\n\t"
                        "or x30, x30, %1\n\t"
                        :
                        : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
                        : "x30"
                        );
                    printf("motor1_reg=%d\n",motor1_reg);//sahil
                    printf("motor2_reg=%d\n",motor2_reg);//sahil
                    printf("motor1=%d\n",Motor1);//sahil
                    printf("motor2=%d\n",Motor2);//sahil


                    // Delay 200 milliseconds
                    for (int i = 0; i < 200000; i++);
                  } 
                  
                  else 
                    {
                      // Start motors
                      
                      Motor1 = 1;
                      Motor2 = 1;

                      // Calculate the motor control values
                      motor1_reg = Motor1 * 4;
                      motor2_reg = Motor2 * 8;

                      
                      // Use inline assembly to control motors
                    asm volatile (
                        "and x30, x30, %2\n\t"
                        "or x30, x30, %0\n\t"
                        "or x30, x30, %1\n\t"
                        :
                        : "r"(motor1_reg), "r"(motor2_reg), "r"(mask1)
                        : "x30"
                        );
                      printf("motor1_reg=%d\n",motor1_reg);//sahil
                      printf("motor2_reg=%d\n",motor2_reg);//sahil
                      printf("motor1=%d\n",Motor1);//sahil
                      printf("motor2=%d\n",Motor2);//sahil
          
                    }
                  
              
        
        }
        distance=distance-1;
    }
    return 0;
}

```
- **spike simulation**
``` I have used my friend's laptop cause spike wasn't working on mine```

![WhatsApp Image 2023-10-26 at 9 59 30 PM (1)](https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/7438b6a7-c227-4e7a-85fd-1e88c3278fcc)
![WhatsApp Image 2023-10-26 at 9 59 30 PM](https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/aae9f6a3-0812-412f-8775-b48ed8bd9f08)
![WhatsApp Image 2023-10-26 at 9 59 29 PM](https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/70b72216-1b0f-4700-819c-076dc5746003)

# Functional Simualation

We will perform functional simulation to test the functionality of the verilog code generated for the processor chip. We have tested the processor and its functionality for various input combinations and compare the output generated with the desired expected output. The processor and testbench code are under the file name ```processor.v``` and ```testbench.v```. The files can be found in the repository above.




- input - 11, expected output -  000/100
<img width="707" alt="11" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/81ad77bb-7761-4315-9f7a-be388af050a2">

- input - 10, expected output - 011/111
<img width="504" alt="10" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/35152986-2966-47ec-a4d4-0c5a1967bf20">

- input - 01, expected output - 000/100
<img width="677" alt="01" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/8d4dd151-b998-45fd-b61f-16cf3b19c1e0">

- input - 00, expected output - 000
<img width="575" alt="00" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/d2f898d8-b924-47b9-b369-7ee2f50772cf">


# Instruction Verification

We will consider the link: ```https://en.wikichip.org/wiki/risc-v/registers``` for refrence and decide the signal pins. Thus, according to the reference given, ```signal43``` is zero register, ```signal45``` is the stack pointer, and ```signal58``` is the a5 register.

Some of the instructions in the above assembly code were tested in GTKWave and was verified.

**addi sp,sp,-48**
Here we will conside the assembly code line:
```10054:	fd010113          	addi	sp,sp,-48```
We can observe default value of sp is FF after that it becomes AF which is -80 in hexadecimal.

Input instruction - 00000000

Output instruction - FB010113

<img width="726" alt="4" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/93212fdb-fed6-4c22-b259-baa786ac40f9">


**li	a5,1**
Here we will conside the assembly code line:
```10060:	00100793          	li	a5,1```

We can see for the instruction 00100793 $signal$58 output will be 0000001.

<img width="931" alt="5" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/aa56d845-517f-478c-b5de-dd7ae672ed90">
<img width="700" alt="3" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/6baaf9c3-3f16-460d-b467-c7f029110c2c">

# The below screenshots are of mutiple possible cases of inputs

- We see the input 10 produces the outputf 011 
<img width="775" alt="1" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/238ff7a5-ee4f-4afd-b97e-7efba637f1fd">
When the output is 011 the instruction is 001F7793 as shown above.

- We see the input 11 produces the output 000
<img width="699" alt="2" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/84f6afd9-598d-4f9d-a017-1b168348241f">
When the output is becoming low the instruction is 00FF6F33 as shown above.


## Gate Level Synthesis

Here we do Synthesis of our processor on yosys using the following commands:

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog <filename.v>

```

The following Command is used to run the synthesized netlist along with primitives.<br />

```
iverilog -o test testbench.v synth_processor_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
```

The following waveforms are of GLS Simulation obtained using GTKWave and the same output is obtained as Functional Verification.<br />

<img width="673" alt="00" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/6e64895f-23ee-48ef-9121-195e62f7aa56">

<img width="638" alt="01" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/c866ca89-4c14-48d0-8d67-0b839f768668">

<img width="665" alt="10" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/528cefbe-dc72-4682-ae0d-2df14bc4ee55">

<img width="756" alt="11" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/5279a5ca-eab9-4498-b15b-3832b3f132e5">

The following screenshot is of the wrapper module using the following command in yosys

```
show wrapper
```
<img width="565" alt="wrapper" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/c108223f-01d7-4b22-bd4d-0e0fdaef05b8">

# Physical Design

Place and Route (PnR) is the core of any ASIC implementation and Openlane flow integrates into it several key open source tools which perform each of the respective stages of PnR. Below are the stages and the respective tools that are called by openlane for the functionalities as described:<br />

<img width="408" alt="Screenshot 2023-11-25 215932" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/e1bda3c1-af13-4d4b-b0af-0c0f6b18bb57">



- Synthesis
  - Generating gate-level netlist
  -  Performing cell mapping
  -   Performing pre-layout STA
- Floorplaning
  - Defining the core area for the macro as well as the cell sites and the tracks
  - Placing the macro input and output ports
  - Generating the power distribution network
- Placement
  - Performing global placemen
  - Perfroming detailed placement to legalize the globally placed components
- Clock Tree Synthesis
  - Synthesizing the clock tree
- Routing
  - Performing global routing to generate a guide file for the detailed router
  - Performing detailed routing
- GDSII
  - Streaming out the final GDSII layout file from the routed def
 
## Preparing the Design
`
```bash
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project
% run_synthesis; run_floorplan; run_placement; run_cts; gen_pdn; run_routing

```

<img width="865" alt="1" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/5c62fada-ca90-49a9-867a-9f26071e4f3d">

Completion of routing 

<img width="868" alt="2" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/7768db6b-9d6a-4421-92a4-10f3b6ac5a3f">

Sign off steps 

```bash
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check
```

<img width="864" alt="3" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/8179a033-8e61-44b8-a36f-107ac828ab9c">


## Reports 

***SYNTHESIS***

- Logic synthesis uses the RTL netlist to perform HDL technology mapping. The synthesis process is normally performed in two major steps:
  - GTECH Mapping – Consists of mapping the HDL netlist to generic gates what are used to perform logical optimization based on AIGERs and other topologies created from the generic mapped netlist
  - Technology Mapping – Consists of mapping the post-optimized GTECH netlist to standard cells described in the PDK.

- To synthesize the code run the following command.
```bash
run_synthesis
```

<img width="920" alt="synth_log" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/4fbba84e-cdfa-4061-853c-0fcd0bdde643">

***FLOORPLAN***

- Goal is to plan the silicon area and create a robust power distribution network (PDN) to power each of the individual components of the synthesized netlist. In addition, macro placement and blockages must be defined before placement occurs to ensure a legalized GDS file. In power planning we create the ring which is connected to the pads which brings power around the edges of the chip. We also include power straps to bring power to the middle of the chip using higher metal layers which reduces IR drop and electro-migration problem.

- Following command helps to run floorplan:

```bash
run_floorplan
```

- to view the floorplan on Magic from ```results/floorplan```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```
<img width="950" alt="floorplan" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/eef4f868-9549-4119-be27-2bc6f371726c">

- Core Area after floorplan

<img width="710" alt="core_area" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/1e0602e5-cae7-4f23-a028-85ace33e6d76">

- Die Area after floorplan

<img width="802" alt="die_area" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/1130bbd1-5bdc-4957-9e84-6e40aee08dca">


***PLACEMENT***

- Place the standard cells on the floorplane rows, aligned with sites defined in the technology lef file. Placement is done in two steps: Global and Detailed. In Global placement tries to find optimal position for all cells but they may be overlapping and not aligned to rows, detailed placement takes the global placement and legalizes all of the placements trying to adhere to what the global placement wants. The next step in the OpenLANE ASIC flow is placement. The synthesized netlist is to be placed on the floorplan. Placement is perfomed in 2 stages:
  - Global Placement
  - Detailed Placement

- Run the following command to run the placement:

```bash
run_placement
```

- to view the placement on Magic from ```results/placement```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

<img width="954" alt="placement" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/c74e3b1b-8cc1-4941-aac7-383b091848e5">



***CLOCK TREE SYNTHESIS***

Clock tree synteshsis is used to create the clock distribution network that is used to deliver the clock to all sequential elements. The main goal is to create a network with minimal skew across the chip. H-trees are a common network topology that is used to achieve this goal.

The purpose of building a clock tree is enable the clock input to reach every element and to ensure a zero clock skew. H-tree is a common methodology followed in CTS.
Following command is used to run CTS.

```bash
run_cts
```

- Timimg Report

<img width="650" alt="timing" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/b0c2cd41-1800-4a1b-b466-87ced7686486">

- Area Report

<img width="628" alt="area" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/28308c61-43de-4928-b60f-14e2e5ea87a7">

- Skew Report

<img width="584" alt="skew" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/309e1003-558d-48de-b606-a73c58fb10bf">

- Power Report

<img width="606" alt="power" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/51257a42-e07a-4ca4-a34c-59eadf062a63">


***POWER NETWORK DISTRIBUTION***

- The commmand to establish power distribution network is as follows

```bash
gen_pdn
```

***ROUTING***

- Implements the interconnect system between standard cells using the remaining available metal layers after CTS and PDN generation. The routing is performed on routing grids to ensure minimal DRC errors.
- OpenLANE uses the TritonRoute tool for routing. There are 2 stages of routing:
  - Global Routing
  - Detailed Routing

- In Global Routing Routing region is divided into rectangle grids which are represented as course 3D routes (Fastroute tool).
- In Detailed Finer grids and routing guides used to implement physical wiring (TritonRoute tool).

- Run the following command to run the routing

```bash
run_routing
```
- The layout can be viewed using MAGIC in ```results/routing```

```bash
 magic -T ~/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

<img width="965" alt="routing" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/8dea85e1-4f21-4fa3-aab9-7427b8dad7e3">

- Area of Design

<img width="614" alt="magic" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/bfcfebfd-3ae5-4b24-87df-e4570395cb30">

- Post Routing Reports
  
  -  Timing

<img width="694" alt="rout_timing" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/9a597efe-cb42-4ca0-8c76-e49295f1dd74">

  -  Area
 
<img width="655" alt="rout_area" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/6e5dff8e-211e-4127-802d-36a009b0ae1c">
 
  -  Power

<img width="685" alt="rout_power" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/04642826-d1e5-4c91-9842-80f59df248dd">
 
  -  Design Rule Check (DRC)

<img width="691" alt="DRC" src="https://github.com/SahilSira/ASIC_Project_Automatic_Stopping_Car/assets/140998855/b48e2ca7-ecfb-4007-8eb1-c7bf76c5706b">

# Word of Thanks

I would take this opportunity to sciencerly thank Mr. Kunal Gosh(Founder/VSD) for helping me out to complete this flow smoothly.

Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- OpenAI Chatgpt
- Shant Rakshit, MTech, IIITB
- Emil Jayanth Lal, MTech, IIITB
- Mayank Kabra, Founder, Chipcron Pvt.Ltd.
- Tushar Mavi, MTech, IIITB
- Kanish R, MTech, IIITB
