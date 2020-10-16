#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include "RdtReceiver.h"
#include "SlideWindow.h"
#include <memory>
#include <vector>
using std::pair;
using std::shared_ptr;
using std::vector;
class TCPRdtReceiver : public RdtReceiver, public SlideWindow {
private:
  shared_ptr<Packet> lastAckPkt;                           //上次发送的确认报文
  vector<pair<shared_ptr<Packet>, int>> waitingDeliverPkt; // 缓存的失序数据包

private:
  shared_ptr<Packet> makePacket(int seqNum); // 制作Ack包
  void slide(const Packet &ackPkt);          // 滑动窗口
  void removeDataPacket();                   // 将确认了的数据包移除队列
  void deliverPacket();                      // 交付数据
  void printSlideWindow() const;             // 输出滑动窗口的内容
public:
  TCPRdtReceiver();
  ~TCPRdtReceiver() = default;

public:
  // RdtReceiver接口实现
  void receive(const Packet &packet); //接收报文，将被NetworkService调用
};

#endif
