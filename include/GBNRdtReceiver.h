#ifndef GBN_RECEIVER_H
#define GBN_RECEIVER_H
#include "RdtReceiver.h"
#include <memory>
using std::shared_ptr;
class GBNRdtReceiver : public RdtReceiver {
private:
  int expectSequenceNumberRcvd;  // 期待收到的下一个报文序号
  shared_ptr<Packet> lastAckPkt; //上次发送的确认报文
  int seqLen;

private:
  shared_ptr<Packet> makePacket(int seqNum); // 制作Ack包

public:
  GBNRdtReceiver();
  ~GBNRdtReceiver() = default;

public:
  // RdtReceiver接口实现
  void receive(const Packet &packet); //接收报文，将被NetworkService调用
};

#endif
