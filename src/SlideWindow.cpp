#include "SlideWindow.h"
#include <iostream>

int SlideWindow::orderMapping(int seqNum) const{
  int result = seqNum - base;
  if (result >= 0 && result < winSize)
    return result;
  else if (result >= winSize)
    return result - seqLength;
  else if (result < -winSize)
    return result + seqLength;
  else if (result < 0 && result >= -winSize)
    return result;
  else {
    return -seqLength;
    throw runtime_error("no that mapping");
  }
}

void SlideWindow::setSeqLength(int len) { seqLength = len; }

void SlideWindow::setWinSize(int size) { winSize = size; }