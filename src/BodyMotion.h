#ifndef _BODYMOTION_H_
#define _BODYMOTION_H_

#if defined(ARDUINO_M5STACK_Core2)
//#define PORT_C
#if defined (PORT_A)
  #define SERVO_PIN_X 33  //Core2 PORT A
  #define SERVO_PIN_Y 32
#elif defined (PORT_C)
  #define SERVO_PIN_X 14  //Core2 PORT C (INTERNAL UART2)
  #define SERVO_PIN_Y 13
#endif
#elif defined( ARDUINO_M5STACK_FIRE )
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#elif defined( ARDUINO_M5Stack_Core_ESP32 )
  #define SERVO_PIN_X 21
  #define SERVO_PIN_Y 22
#elif defined( ARDUINO_M5STACK_CORES3 )
  #if defined (PORT_A)
    #define SERVO_PIN_X 2  //CoreS3 PORT A
    #define SERVO_PIN_Y 1
  #elif defined (PORT_C)
    #define SERVO_PIN_X 18  //CoreS3 PORT C
    #define SERVO_PIN_Y 17
  #endif
#endif

// Temporary default value to avoid compile errors before build_flags are set in platformio.ini.
// Please specify your port and device stack via build_flags in platform.ini for actual use.
#ifndef SERVO_PIN_X
#define SERVO_PIN_X 0 
#pragma message("SERVO_PIN_X is not defined. Using default value 0 for editing/IntelliSense.")
#endif
#ifndef SERVO_PIN_Y
#define SERVO_PIN_Y 1
#pragma message("SERVO_PIN_Y is not defined. Using default value 1 for editing/IntelliSense.")
#endif


#define START_DEGREE_VALUE_X 90
#define START_DEGREE_VALUE_Y 85


class BodyMotion {
public:
    BodyMotion();
    void begin(); 

    static int getStartDegreeX() { return START_DEGREE_VALUE_X; }
    static int getStartDegreeY() { return START_DEGREE_VALUE_Y; }

    void moveHomePosition();
    void moveTo(int x, int y);
private:
    int _pinX, _pinY;
};

#endif // _BODYMOTION_H_