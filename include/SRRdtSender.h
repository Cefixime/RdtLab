#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "RdtSender.h"
#include "SlideWindow.h"
#include <memory>
#include <vector>
#define SEQ_LEN 8
using std::pair;
using std::shared_ptr;
using std::vector;
class SRRdtSender : public RdtSender, public SlideWindow {
private:
  enum SendState { TRANSPORT, FULL };                     // 声明状态枚举
  SendState state{TRANSPORT};                             // 当前状态
  vector<pair<shared_ptr<Packet>, int>> packetWaitingAck; // 已发送并等待Ack的数据包

private:
  shared_ptr<Packet> makePacket(const Message &message); // 制作数据包
  void slide(const Packet &ackPkt) override;       // 滑动窗口                                  // 将确认了的数据包移除队列

public:
  // RdtSender 接口实现
  bool getWaitingState() override;
  bool send(const Message &message) override;  //发送应用层下来的Message，由NetworkServiceSimulator调用
  void receive(const Packet &ackPkt) override; //接受确认Ack，将被NetworkServiceSimulator调用
  void timeoutHandler(int seqNum) override;    // Timeout handler，将被NetworkServiceSimulator调用

public:
  void printSlideWindow() const override; // 输出滑动窗口的内容
  SRRdtSender() = default;
  ~SRRdtSender() = default;
};

#endif
