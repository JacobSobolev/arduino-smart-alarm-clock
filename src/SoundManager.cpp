#include <SoundManager.h>

SoundManager::SoundManager()
: _buzzerPinNumber(12), _startIndexPhase1(200), _startIndexPhase3(800),
_delayLoop1(5), _delayLoop2(10), _delayBetween(1000)
{
  _index = _startIndexPhase1;
  _playMusic = false;
  _playedTone = false;
  _phase = 0;
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
  // Serial.println(_index);

  if (_playMusic){
    if (_phase == 0){
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
      else
      {
        _phase = 1;
        _index = 0;
      }
    }
    else if (_phase == 1){
      _delayCounter ++;
      if (_delayCounter >= _delayBetween)
      {
        _index = _startIndexPhase3;
        _playedTone = false;
        _phase = 2;
      }
    }
    else if (_phase == 2){
      if (_index > 200){
        if (!_playedTone){
          tone(_buzzerPinNumber,_index);
          _delayCounter = 0;
          _playedTone = true;
        }
        else{
          _delayCounter ++;
          if (_delayCounter >= _delayLoop2){
            _index--;
            _playedTone = false;

          }
        }
      }
      else
      {
        _phase = 3;
      }
    }
    else{
      _phase = 0;
      _index = _startIndexPhase1;
      _playedTone = false;
      // noTone(_buzzerPinNumber);
    }
  }
  else {
    noTone(_buzzerPinNumber);
  }
}

void SoundManager::setPlayMusic(boolean play)
{
  _playMusic = play;
  _index = _startIndexPhase1;
  _phase = 0;
}

boolean SoundManager::getPlayMusic()
{
  return _playMusic;
}
