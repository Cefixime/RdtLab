#ifndef GBN_SENDER_H
#define GBN_SENDER_H
#include "RdtSender.h"
#include <memory>
#include <vector>
#define SEQ_LEN 8
using std::shared_ptr;
class GBNRdtSender : public RdtSender {
private:
  enum SendState { START, TRANSPORT, FULL, FINISH }; // 声明状态枚举
  SendState state{START};                            // 当前状态
  int winSize{SEQ_LEN / 2};                          // 窗口大小
  int seqLength{SEQ_LEN};                            // 序列长度
  int base{0};                                       // 窗口的base, 其值为[0, Length) 中的整数
  int nextSeqNum{0};                                 // 窗口的下一个可用packet的序号
  std::vector<shared_ptr<Packet>> packetWaitingAck;  // 已发送并等待Ack的数据包

public:
  // RdtSender 接口实现
  bool getWaitingState() override;
  bool send(const Message &message) override;  //发送应用层下来的Message，由NetworkServiceSimulator调用
  void receive(const Packet &ackPkt) override; //接受确认Ack，将被NetworkServiceSimulator调用
  void timeoutHandler(int seqNum) override;    // Timeout handler，将被NetworkServiceSimulator调用

private:
  shared_ptr<Packet> makePacket(const Message &message); // 制作数据包
  void slideWindow(const Packet &ackPkt);     // 滑动窗口
  int orderMapping(int seqNum);               // 将 “模Length” 的序号转化为相对base的正向偏移
  void goBackN();                             // 重发所有已发送，等待Ack的数据包
  void removePacket();                        // 将确认了的数据包移除队列

public:
  void setSeqNum(int len);
  void printSlideWindow() const;  // 输出滑动窗口的内容
  GBNRdtSender() = default;
  ~GBNRdtSender() = default;
};

#endif
