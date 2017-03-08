#include <LightManager.h>

LightManager::LightManager()
:_pinNumber(0)
{
  _currentValue = 0;
  _alarmValue = 0;
}

LightManager::~LightManager(){

}

void LightManager::init(){
  pinMode(_pinNumber,INPUT);
}

void LightManager::updateLightValue(){
  _currentValue = analogRead(_pinNumber);
}

int LightManager::getCurrentValue(){
  return _currentValue;
}

void LightManager::setAlarmValue(int value){
  _alarmValue = value;
}

int LightManager::getAlarmValue(){
  return _alarmValue;
}

void LightManager::addToAlarmValue(int valueToAdd)
{
  _alarmValue += valueToAdd;
}

bool LightManager::isAlarmValuePassed()
{
  return _currentValue >= _alarmValue;
}
