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

00010094 <main>:
   10094:	fe010113          	add	sp,sp,-32
   10098:	00112e23          	sw	ra,28(sp)
   1009c:	00812c23          	sw	s0,24(sp)
   100a0:	02010413          	add	s0,sp,32
   100a4:	000117b7          	lui	a5,0x11
   100a8:	3b47a783          	lw	a5,948(a5) # 113b4 <Motor1>
   100ac:	00279793          	sll	a5,a5,0x2
   100b0:	fef42623          	sw	a5,-20(s0)
   100b4:	000117b7          	lui	a5,0x11
   100b8:	3b87a783          	lw	a5,952(a5) # 113b8 <Motor2>
   100bc:	00279793          	sll	a5,a5,0x2
   100c0:	fef42423          	sw	a5,-24(s0)
   100c4:	00ef6f33          	or	t5,t5,a4
   100c8:	00ff6f33          	or	t5,t5,a5
   100cc:	fee42623          	sw	a4,-20(s0)
   100d0:	fef42423          	sw	a5,-24(s0)
   100d4:	008000ef          	jal	100dc <read>
   100d8:	ffdff06f          	j	100d4 <main+0x40>

000100dc <read>:
   100dc:	ff010113          	add	sp,sp,-16
   100e0:	00112623          	sw	ra,12(sp)
   100e4:	00812423          	sw	s0,8(sp)
   100e8:	01010413          	add	s0,sp,16
   100ec:	001f7713          	and	a4,t5,1
   100f0:	80e1aa23          	sw	a4,-2028(gp) # 113c8 <switch_val>
   100f4:	8141a783          	lw	a5,-2028(gp) # 113c8 <switch_val>
   100f8:	00078863          	beqz	a5,10108 <read+0x2c>
   100fc:	020000ef          	jal	1011c <pulse_count>
   10100:	8001a823          	sw	zero,-2032(gp) # 113c4 <pulse_counter>
   10104:	228000ef          	jal	1032c <delay_100ms>
   10108:	00000013          	nop
   1010c:	00c12083          	lw	ra,12(sp)
   10110:	00812403          	lw	s0,8(sp)
   10114:	01010113          	add	sp,sp,16
   10118:	00008067          	ret

0001011c <pulse_count>:
   1011c:	ff010113          	add	sp,sp,-16
   10120:	00112623          	sw	ra,12(sp)
   10124:	00812423          	sw	s0,8(sp)
   10128:	01010413          	add	s0,sp,16
   1012c:	03c000ef          	jal	10168 <trigger_send>
   10130:	002f7713          	and	a4,t5,2
   10134:	80e1a623          	sw	a4,-2036(gp) # 113c0 <echo>
   10138:	0100006f          	j	10148 <pulse_count+0x2c>
   1013c:	8101a783          	lw	a5,-2032(gp) # 113c4 <pulse_counter>
   10140:	00178713          	add	a4,a5,1
   10144:	80e1a823          	sw	a4,-2032(gp) # 113c4 <pulse_counter>
   10148:	80c1a783          	lw	a5,-2036(gp) # 113c0 <echo>
   1014c:	fe0798e3          	bnez	a5,1013c <pulse_count+0x20>
   10150:	074000ef          	jal	101c4 <distance_calc>
   10154:	00000013          	nop
   10158:	00c12083          	lw	ra,12(sp)
   1015c:	00812403          	lw	s0,8(sp)
   10160:	01010113          	add	sp,sp,16
   10164:	00008067          	ret

00010168 <trigger_send>:
   10168:	fe010113          	add	sp,sp,-32
   1016c:	00112e23          	sw	ra,28(sp)
   10170:	00812c23          	sw	s0,24(sp)
   10174:	02010413          	add	s0,sp,32
   10178:	00100713          	li	a4,1
   1017c:	80e1a423          	sw	a4,-2040(gp) # 113bc <trigger>
   10180:	8081a783          	lw	a5,-2040(gp) # 113bc <trigger>
   10184:	00379793          	sll	a5,a5,0x3
   10188:	fef42623          	sw	a5,-20(s0)
   1018c:	00ef6f33          	or	t5,t5,a4
   10190:	80e1aa23          	sw	a4,-2028(gp) # 113c8 <switch_val>
   10194:	158000ef          	jal	102ec <delay_10us>
   10198:	8001a423          	sw	zero,-2040(gp) # 113bc <trigger>
   1019c:	8081a783          	lw	a5,-2040(gp) # 113bc <trigger>
   101a0:	00379793          	sll	a5,a5,0x3
   101a4:	fef42623          	sw	a5,-20(s0)
   101a8:	00ef6f33          	or	t5,t5,a4
   101ac:	80e1aa23          	sw	a4,-2028(gp) # 113c8 <switch_val>
   101b0:	00000013          	nop
   101b4:	01c12083          	lw	ra,28(sp)
   101b8:	01812403          	lw	s0,24(sp)
   101bc:	02010113          	add	sp,sp,32
   101c0:	00008067          	ret

000101c4 <distance_calc>:
   101c4:	fe010113          	add	sp,sp,-32
   101c8:	00112e23          	sw	ra,28(sp)
   101cc:	00812c23          	sw	s0,24(sp)
   101d0:	02010413          	add	s0,sp,32
   101d4:	8101a703          	lw	a4,-2032(gp) # 113c4 <pulse_counter>
   101d8:	00070793          	mv	a5,a4
   101dc:	00179793          	sll	a5,a5,0x1
   101e0:	00e787b3          	add	a5,a5,a4
   101e4:	00279793          	sll	a5,a5,0x2
   101e8:	40e787b3          	sub	a5,a5,a4
   101ec:	00279793          	sll	a5,a5,0x2
   101f0:	40e787b3          	sub	a5,a5,a4
   101f4:	00279793          	sll	a5,a5,0x2
   101f8:	fef42623          	sw	a5,-20(s0)
   101fc:	fec42703          	lw	a4,-20(s0)
   10200:	00f00793          	li	a5,15
   10204:	00e7c863          	blt	a5,a4,10214 <distance_calc+0x50>
   10208:	088000ef          	jal	10290 <stop>
   1020c:	164000ef          	jal	10370 <delay_200ms>
   10210:	0080006f          	j	10218 <distance_calc+0x54>
   10214:	018000ef          	jal	1022c <move_forward>
   10218:	00000013          	nop
   1021c:	01c12083          	lw	ra,28(sp)
   10220:	01812403          	lw	s0,24(sp)
   10224:	02010113          	add	sp,sp,32
   10228:	00008067          	ret

0001022c <move_forward>:
   1022c:	fe010113          	add	sp,sp,-32
   10230:	00812e23          	sw	s0,28(sp)
   10234:	02010413          	add	s0,sp,32
   10238:	000117b7          	lui	a5,0x11
   1023c:	00100713          	li	a4,1
   10240:	3ae7aa23          	sw	a4,948(a5) # 113b4 <Motor1>
   10244:	000117b7          	lui	a5,0x11
   10248:	00100713          	li	a4,1
   1024c:	3ae7ac23          	sw	a4,952(a5) # 113b8 <Motor2>
   10250:	000117b7          	lui	a5,0x11
   10254:	3b47a783          	lw	a5,948(a5) # 113b4 <Motor1>
   10258:	00279793          	sll	a5,a5,0x2
   1025c:	fef42623          	sw	a5,-20(s0)
   10260:	000117b7          	lui	a5,0x11
   10264:	3b87a783          	lw	a5,952(a5) # 113b8 <Motor2>
   10268:	00279793          	sll	a5,a5,0x2
   1026c:	fef42423          	sw	a5,-24(s0)
   10270:	00ef6f33          	or	t5,t5,a4
   10274:	00ff6f33          	or	t5,t5,a5
   10278:	fee42623          	sw	a4,-20(s0)
   1027c:	fef42423          	sw	a5,-24(s0)
   10280:	00000013          	nop
   10284:	01c12403          	lw	s0,28(sp)
   10288:	02010113          	add	sp,sp,32
   1028c:	00008067          	ret

00010290 <stop>:
   10290:	fe010113          	add	sp,sp,-32
   10294:	00812e23          	sw	s0,28(sp)
   10298:	02010413          	add	s0,sp,32
   1029c:	000117b7          	lui	a5,0x11
   102a0:	3a07aa23          	sw	zero,948(a5) # 113b4 <Motor1>
   102a4:	000117b7          	lui	a5,0x11
   102a8:	3a07ac23          	sw	zero,952(a5) # 113b8 <Motor2>
   102ac:	000117b7          	lui	a5,0x11
   102b0:	3b47a783          	lw	a5,948(a5) # 113b4 <Motor1>
   102b4:	00279793          	sll	a5,a5,0x2
   102b8:	fef42623          	sw	a5,-20(s0)
   102bc:	000117b7          	lui	a5,0x11
   102c0:	3b87a783          	lw	a5,952(a5) # 113b8 <Motor2>
   102c4:	00279793          	sll	a5,a5,0x2
   102c8:	fef42423          	sw	a5,-24(s0)
   102cc:	00ef6f33          	or	t5,t5,a4
   102d0:	00ff6f33          	or	t5,t5,a5
   102d4:	fee42623          	sw	a4,-20(s0)
   102d8:	fef42423          	sw	a5,-24(s0)
   102dc:	00000013          	nop
   102e0:	01c12403          	lw	s0,28(sp)
   102e4:	02010113          	add	sp,sp,32
   102e8:	00008067          	ret

000102ec <delay_10us>:
   102ec:	fe010113          	add	sp,sp,-32
   102f0:	00812e23          	sw	s0,28(sp)
   102f4:	02010413          	add	s0,sp,32
   102f8:	fe042623          	sw	zero,-20(s0)
   102fc:	0100006f          	j	1030c <delay_10us+0x20>
   10300:	fec42783          	lw	a5,-20(s0)
   10304:	00178793          	add	a5,a5,1
   10308:	fef42623          	sw	a5,-20(s0)
   1030c:	fec42703          	lw	a4,-20(s0)
   10310:	00900793          	li	a5,9
   10314:	fee7d6e3          	bge	a5,a4,10300 <delay_10us+0x14>
   10318:	00000013          	nop
   1031c:	00000013          	nop
   10320:	01c12403          	lw	s0,28(sp)
   10324:	02010113          	add	sp,sp,32
   10328:	00008067          	ret

0001032c <delay_100ms>:
   1032c:	fe010113          	add	sp,sp,-32
   10330:	00812e23          	sw	s0,28(sp)
   10334:	02010413          	add	s0,sp,32
   10338:	fe042623          	sw	zero,-20(s0)
   1033c:	0100006f          	j	1034c <delay_100ms+0x20>
   10340:	fec42783          	lw	a5,-20(s0)
   10344:	00178793          	add	a5,a5,1
   10348:	fef42623          	sw	a5,-20(s0)
   1034c:	fec42703          	lw	a4,-20(s0)
   10350:	000187b7          	lui	a5,0x18
   10354:	69f78793          	add	a5,a5,1695 # 1869f <__global_pointer$+0x6aeb>
   10358:	fee7d4e3          	bge	a5,a4,10340 <delay_100ms+0x14>
   1035c:	00000013          	nop
   10360:	00000013          	nop
   10364:	01c12403          	lw	s0,28(sp)
   10368:	02010113          	add	sp,sp,32
   1036c:	00008067          	ret

00010370 <delay_200ms>:
   10370:	fe010113          	add	sp,sp,-32
   10374:	00812e23          	sw	s0,28(sp)
   10378:	02010413          	add	s0,sp,32
   1037c:	fe042623          	sw	zero,-20(s0)
   10380:	0100006f          	j	10390 <delay_200ms+0x20>
   10384:	fec42783          	lw	a5,-20(s0)
   10388:	00178793          	add	a5,a5,1
   1038c:	fef42623          	sw	a5,-20(s0)
   10390:	fec42703          	lw	a4,-20(s0)
   10394:	000317b7          	lui	a5,0x31
   10398:	d3f78793          	add	a5,a5,-705 # 30d3f <__global_pointer$+0x1f18b>
   1039c:	fee7d4e3          	bge	a5,a4,10384 <delay_200ms+0x14>
   103a0:	00000013          	nop
   103a4:	00000013          	nop
   103a8:	01c12403          	lw	s0,28(sp)
   103ac:	02010113          	add	sp,sp,32
   103b0:	00008067          	ret




```

# Unique Instructions
```bash
Number of different instructions: 18
List of unique instructions:
blt
bge
sub
bnez
or
sw
add
jal
and
nop
mv
lw
ret
sll
beqz
j
li
lui



```
