#ifndef SR_RECEIVER_H
#define SR_RECEIVER_H
#include "RdtReceiver.h"
#include "SlideWindow.h"
#include <memory>
#include <vector>
#define SEQ_LEN 8
using std::shared_ptr;
class SRRdtReceiver : public RdtReceiver, public SlideWindow {
private:
  std::vector<pair<shared_ptr<Packet>, int>> waitingDeliverPkt; // 等待交付的数据包

private:
  shared_ptr<Packet> makePacket(int seqNum); // 制作Ack包
  void slideWindow(const Packet &ackPkt);    // 滑动窗口
  int orderMapping(int seqNum);              // 将 “模Length” 的序号转化为相对base的正向偏移
  void removeDataPacket();                   // 将确认了的数据包移除队列
  void printSlideWindow() const;             // 输出滑动窗口的内容
public:
  SRRdtReceiver() = default;
  ~SRRdtReceiver() = default;

public:
  // RdtReceiver接口实现
  void receive(const Packet &packet); //接收报文，将被NetworkService调用
};

#endif
