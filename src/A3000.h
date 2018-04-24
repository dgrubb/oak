/*
 * File: A3000.h
 * Author: dgrubb
 * Date:24/04/2018
 */

#ifndef _A3000_H
#define _A3000_H

#define A3000_SCREEN_WIDTH  800     // pixels
#define A3000_SCREEN_HEIGHT 600     // pixels
#define A3000_CPU_FREQUENCY 8000000 // Hz
#define A3000_RAM_SIZE      2048    // bytes

class A3000 {

public:

    // Constructors and destructors
    A3000();
    ~A3000();

    // Methods
    int Reset();

private:

    // Data

    // Methods
    
};

#endif // _A3000_H
