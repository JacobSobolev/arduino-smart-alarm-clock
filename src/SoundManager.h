#ifndef SOUND_MANAGER
#define SOUND_MANAGER



#include <Arduino.h>
#include <MusicalNotes.h>

class SoundManager {
  private:
    const int _buzzerPinNumber;
    const int _startIndexPhase1;
    const int _startIndexPhase3;
    const int _delayLoop1;
    const int _delayLoop2;
    const int _delayBetween;

    int _index ;
    boolean _playMusic;
    int _delayCounter;
    boolean _playedTone;
    int _phase;

  public:

    SoundManager();
    ~SoundManager();
    void init();
    void playNext();
    void setPlayMusic(boolean play);
    boolean getPlayMusic();

};

#endif
