#include <Arduino.h>
#include <TaskScheduler.h>
#include <AlarmClockManager.h>
#include <SoundManager.h>

AlarmClockManager *alarmClockManager = new AlarmClockManager();
Scheduler runner;

//
void handleInputCallback();
void printOnLcdCallback();
void checkAlarmCallback();
void playAlarmCallback();
void updateLightCallback();
//
Task handleInputTask(100, TASK_FOREVER, &handleInputCallback);
Task printOnLcdTask(100, TASK_FOREVER, &printOnLcdCallback);
Task checkAlarmTask(1, TASK_FOREVER, &checkAlarmCallback);
Task playAlarmTask(1, TASK_FOREVER, &playAlarmCallback);
Task updateLightTask(500, TASK_FOREVER, &updateLightCallback);
//
void handleInputCallback() {
  alarmClockManager->handleButtonsInput();
}

void printOnLcdCallback() {
  alarmClockManager->printCurrentMenu();
}
//
void checkAlarmCallback() {
  alarmClockManager->checkAlarm();
}

void playAlarmCallback() {
  alarmClockManager->playAlarm();
}

void updateLightCallback()
{
  alarmClockManager->updateLightValue();
}



void setup()
{
  // Serial.begin(9600);
  alarmClockManager->init();

  runner.addTask(handleInputTask);
  runner.addTask(printOnLcdTask);
  runner.addTask(checkAlarmTask);
  runner.addTask(playAlarmTask);
  runner.addTask(updateLightTask);
  handleInputTask.enable();
  printOnLcdTask.enable();
  checkAlarmTask.enable();
  playAlarmTask.enable();
  updateLightTask.enable();
}

void loop(){
  runner.execute();
}
