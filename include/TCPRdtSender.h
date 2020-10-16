#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
#include "SlideWindow.h"
#include <memory>
#include <vector>
using std::shared_ptr;
class TCPRdtSender : public RdtSender, public SlideWindow {
private:
  enum SendState { START, TRANSPORT, FULL, FINISH }; // 声明状态枚举
  SendState state{START};                            // 当前状态
  std::vector<shared_ptr<Packet>> packetWaitingAck;  // 已发送并等待Ack的数据包
  int ackRedundant{0};                               // 冗余的Ack
public:
  // RdtSender 接口实现
  bool getWaitingState() override;
  bool send(const Message &message) override;  //发送应用层下来的Message，由NetworkServiceSimulator调用
  void receive(const Packet &ackPkt) override; //接受确认Ack，将被NetworkServiceSimulator调用
  void timeoutHandler(int seqNum) override;    // Timeout handler，将被NetworkServiceSimulator调用

private:
  shared_ptr<Packet> makePacket(const Message &message); // 制作数据包
  void fastResend();                                     // 快速重传
  void slide(const Packet &ackPkt) override;             // 滑动窗口
  void removePacket();                                   // 将确认了的数据包移除队列

public:
  void printSlideWindow() const override; // 输出滑动窗口的内容
  TCPRdtSender() = default;
  ~TCPRdtSender() = default;
};

#endif
