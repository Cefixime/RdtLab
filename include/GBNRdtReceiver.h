#ifndef GBN_RECEIVER_H
#define GBN_RECEIVER_H
#include "RdtReceiver.h"
class GBNRdtReceiver : public RdtReceiver {
  private:
    int expectSequenceNumberRcvd; // 期待收到的下一个报文序号
    Packet lastAckPkt;            //上次发送的确认报文

  private:
    Packet makePacket(int seqNum); // 制作Ack包

  public:
    GBNRdtReceiver();
    virtual ~GBNRdtReceiver();

  public:
    // RdtReceiver接口实现
    void receive(const Packet &packet); //接收报文，将被NetworkService调用
};

#endif
