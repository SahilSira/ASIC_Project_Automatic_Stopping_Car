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
