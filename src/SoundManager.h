#ifndef SOUND_MANAGER
#define SOUND_MANAGER



#include <Arduino.h>
#include <MusicalNotes.h>

class SoundManager {
  private:
    const int _buzzerPinNumber;

    int _delayLoop1;
    int _delayLoop2;
    int _delayBetween();

    int _delayCounter;
    boolean _playedTone;

  public:
    int _index ;
    boolean _playMusic;
    SoundManager();
    ~SoundManager();
    void init();
    void playNext();

};

#endif
