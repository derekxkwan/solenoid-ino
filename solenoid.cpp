#include <Arduino.h>
#include "solenoid.h"

Solenoid::Solenoid(int pin, unsigned long engage_time, unsigned long period)
{
  pinMode(pin, OUTPUT);
  this->_pin = pin;
  this->activated = false;
  this->_start_time = 0UL;
  this->_engage_time = engage_time;
  this->_period = period;
  this->enabled = false;

}

unsigned long Solenoid::get_period(void)
{
  return this->_period;  
}

void Solenoid::enable(bool to_enable)
{
  this->enabled = to_enable;
  if(to_enable == false)
  {
    if(this->activated == true) digitalWrite(_pin, LOW);
    this->activated = false;
  };
  this->_start_time = 0UL;
  //if(this->enabled == true) Serial.println("ENABLED"); else Serial.println("DISABLED");
}

void Solenoid::set_period(unsigned long period)
{
  this->_period = period;
  //Serial.println(this->_period);
}

void Solenoid::set_engage_time(unsigned long engage_time)
{
  this->_engage_time = engage_time;
}

void Solenoid::activate(unsigned long cur_ms)
{
  digitalWrite(_pin, HIGH);
  this->_start_time = cur_ms;
  this->activated = true;

}

void Solenoid::deactivate(void)
{
  digitalWrite(_pin, LOW);
  this->activated = false;


}

void Solenoid::update_status(unsigned long cur_ms)
{

  if((this->activated == true || this->_period > 0UL) && this->enabled == true)
  {
    unsigned long active_time = cur_ms - _start_time;
    if((active_time >= this->_engage_time) && this->activated == true)
    {
      this->deactivate();
    };
    if(this->_period > 0UL && active_time >= this->_period && this->activated == false)
    {
      this->activate(cur_ms);
    };
  };
  
}
