#include "SRRdtSender.h"
#include "Global.h"
#include "PacketSort.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

shared_ptr<Packet> SRRdtSender::makePacket(const Message &message) {
  shared_ptr<Packet> packet = make_shared<Packet>();
  packet->acknum = -1;
  packet->seqnum = nextSeqNum;
  packet->checksum = 0;
  memcpy(packet->payload, message.data, sizeof(message.data));
  packet->checksum = pUtils->calculateCheckSum(*packet);
  return packet;
}

void SRRdtSender::slide(const Packet &ackPkt) {
  if (packetWaitingAck.empty())
    base = nextSeqNum;
  else {
    int shift = packetWaitingAck.cbegin()->second;
    base = (base + shift) % seqLength;
    for (auto &pkt : packetWaitingAck) {
      pkt.second -= shift;
    }
  }
}

bool SRRdtSender::getWaitingState() { return state == FULL; }

bool SRRdtSender::send(const Message &message) {
  if (getWaitingState())
    return false;
  auto pkt = makePacket(message);
  pUtils->printPacket("发送方发送报文", *pkt);
  pns->sendToNetworkLayer(RECEIVER, *pkt);
  pns->startTimer(SENDER, Configuration::TIME_OUT, pkt->seqnum);
  // 暂存数据包
  packetWaitingAck.push_back(make_pair(pkt, orderMapping(pkt->seqnum)));
  // 启动单独定时器
  nextSeqNum = (nextSeqNum + 1) % seqLength;
  printSlideWindow();
  if (orderMapping(nextSeqNum) == -winSize)
    state = FULL;
  return true;
}

void SRRdtSender::receive(const Packet &ackPkt) {
  int checkSum = pUtils->calculateCheckSum(ackPkt);
  int acknum = ackPkt.acknum;
  auto pred = [this, acknum](const pair<shared_ptr<Packet>, int> &pkt) { return pkt.first->seqnum == acknum; };
  //如果校验和正确，并且确认序号在base之后, 以及未缓存的Ack(对应暂存的数据包没有清除)会被正确接受
  auto pkt = find_if(packetWaitingAck.cbegin(), packetWaitingAck.cend(), pred);
  if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) >= 0 && pkt != packetWaitingAck.cend()) {
    pns->stopTimer(SENDER, ackPkt.acknum);
    pUtils->printPacket("发送方正确收到确认", ackPkt);
    // 接受Ack包, 也即去掉相应的数据暂存包
    packetWaitingAck.erase(pkt);
    if (ackPkt.acknum == base) {
      // 如果是base，则可以滑动窗口了，滑动到第一个未收到Ack的包
      slide(ackPkt);
      state = TRANSPORT;
    }
    printSlideWindow();
  }
}

void SRRdtSender::timeoutHandler(int seqNum) {
  cout << "######计时器超时 包:" << seqNum << "未收到正确Ack\n";
  pns->stopTimer(SENDER, seqNum);
  auto pred = [this, seqNum](const pair<shared_ptr<Packet>, int> &pkt) { return pkt.first->seqnum == seqNum; };
  auto pkt = find_if(packetWaitingAck.cbegin(), packetWaitingAck.cend(), pred);
  if (pkt == packetWaitingAck.cend())
    throw runtime_error("no that packet ");
  pns->sendToNetworkLayer(RECEIVER, *(pkt->first));
  pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
}

void SRRdtSender::printSlideWindow() const {
  cout << "######滑动窗口 [base, nextSeqnum]:";
  cout << '[' << base << ',' << nextSeqNum << "] === { ";
  int index = 0;
  auto it = packetWaitingAck.cbegin();
  auto it_end = packetWaitingAck.cend();
  while (index < winSize) {
    if (it != it_end && it->second == index) {
      cout << it->first->seqnum << ' ';
      it++;
    } else if (index < orderMapping(nextSeqNum))
      cout << "+ ";
    else
      cout << "@ ";
    index++;
  }
  cout << "}\n";
}