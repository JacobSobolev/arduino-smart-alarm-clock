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
//
Task handleInputTask(100, TASK_FOREVER, &handleInputCallback);
Task printOnLcdTask(100, TASK_FOREVER, &printOnLcdCallback);
Task checkAlarmTask(1, TASK_FOREVER, &checkAlarmCallback);
Task playAlarmTask(1, TASK_FOREVER, &playAlarmCallback);
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



void setup()
{
  alarmClockManager->init();

  runner.addTask(handleInputTask);
  runner.addTask(printOnLcdTask);
  runner.addTask(checkAlarmTask);
  runner.addTask(playAlarmTask);
  handleInputTask.enable();
  printOnLcdTask.enable();
  checkAlarmTask.enable();
  playAlarmTask.enable();
}

void loop(){
  runner.execute();
}
