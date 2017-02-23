#include <Arduino.h>
#include <TaskScheduler.h>
#include <AlarmClockManager.h>
#include <SoundManager.h>

AlarmClockManager *alarmClockManager = new AlarmClockManager();
Scheduler runner;

//
void t1Callback();
void t2Callback();
void t3Callback();
void t4Callback();
//
Task t1(100, TASK_FOREVER, &t1Callback);
Task t2(100, TASK_FOREVER, &t2Callback);
Task t3(1, TASK_FOREVER, &t3Callback);
Task t4(1, TASK_FOREVER, &t4Callback);
//
void t1Callback() {
  alarmClockManager->handleButtonsInput();
}

void t2Callback() {
  alarmClockManager->printCurrentMenu();
}
//
void t3Callback() {
  alarmClockManager->playAlarm();
}

void t4Callback() {
  alarmClockManager->checkAlarm();
}

void setup()
{
  alarmClockManager->init();
  Serial.begin(9600);

  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  runner.addTask(t4);
  t1.enable();
  t2.enable();
  t3.enable();
  t4.enable();
}
int count = 1;

void loop(){
  runner.execute();
}
