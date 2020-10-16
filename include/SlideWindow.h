#ifndef SLIDE_WINDOW_H
#define SLIDE_WINDOW_H
#define SEQ_LEN 8
#include "Global.h"
class SlideWindow {
protected:
  int winSize{SEQ_LEN / 2};
  int seqLength{SEQ_LEN};
  int base{0};
  int nextSeqNum{0};
  virtual void printSlideWindow() const = 0;
  virtual void slide(const Packet &ackPkt) = 0; // 滑动窗口
  int orderMapping(int seqNum) const;                 // 将 “模seqLength” 的序号转化为相对base的偏移
  void setSeqLength(int len);
  void setWinSize(int size);
  SlideWindow() = default;
  ~SlideWindow() = default;
};
#endif