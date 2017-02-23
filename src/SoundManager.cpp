#include <SoundManager.h>

SoundManager::SoundManager()
: _buzzerPinNumber(11), _delayLoop1(5)
{
  _playMusic = false;
  _playedTone = false;
  _index = 200;
}

SoundManager::~SoundManager()
{
}

void SoundManager::init()
{
  pinMode(_buzzerPinNumber, OUTPUT);
}

void SoundManager::playNext()
{
  if (_index < 800){
    if (!_playedTone){
      tone(_buzzerPinNumber,_index);
      _delayCounter = 0;
      _playedTone = true;
    }
    else{
      _delayCounter ++;
      if (_delayCounter >= _delayLoop1){
        _index++;
        _playedTone = false;
      }
    }
  }
  else{
    _playMusic = false;
    noTone(_buzzerPinNumber);
  }
}
