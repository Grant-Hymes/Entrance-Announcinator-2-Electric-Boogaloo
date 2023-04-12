#include "xc.h"
#include "FinalProject_ASMLibrary.h"

 void writeColor(int r, int g, int b){ 
    
    // writes red color
    for (int i = 128; i > 0; i = i>>1) {
        if (r&i) {
            write_1();
        } else {
            write_0();
        }
    }
    
    // writes green color
    for (int i = 128; i > 0; i = i>>1) {
        if (g&i) {
            write_1();
        } else {
            write_0();
        }
    }
    
    // writes blue color
    for (int i = 128; i > 0; i = i>>1) {
        if (b&i) {
            write_1();
        } else {
            write_0();
        }
    }
        
    // allows for reset to work     
    delay_100us();
        
}