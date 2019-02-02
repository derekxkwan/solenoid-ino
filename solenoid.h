#ifndef Solenoid_h
#define Solenoid_h

#include <Arduino.h>

//period <= 0 : one-shot, > 0 : autotrig on freq
class Solenoid
{
  public:
    Solenoid(int pin, unsigned long engage_time, unsigned long period);
    void update_status(unsigned long cur_ms);
    void activate(unsigned long cur_ms);
    void set_period(unsigned long period);
    unsigned long get_period(void);
    void set_engage_time(unsigned long engage_time);
    void deactivate(void);
    void enable(bool to_enable);
    bool activated;
    bool enabled;
  private:
    int _pin;
    unsigned long _period;
    unsigned long _engage_time;
    unsigned long _start_time;

  
};


#endif
