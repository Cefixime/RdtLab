#include "GBNRdtSender.h"
#include "Global.h"
#include <algorithm>
#include <memory>
#include <vector>
#define MUTI_TIMER
using namespace std;

void GBNRdtSender::printSlideWindow() const {
  cout << "######滑动窗口 [base, nextSeqnum]:";
  cout << '[' << base << ',' << nextSeqNum << "] === { ";
  int count = 0;
  for (auto &pkt : packetWaitingAck) {
    cout << pkt->seqnum << ' ';
    count++;
  }
  while (count++ < winSize) {
    cout << '@' << ' ';
  }
  cout << "}\n";
}

shared_ptr<Packet> GBNRdtSender::makePacket(const Message &message) {
  shared_ptr<Packet> packet = make_shared<Packet>();
  packet->acknum = -1;
  packet->seqnum = nextSeqNum;
  packet->checksum = 0;
  memcpy(packet->payload, message.data, sizeof(message.data));
  packet->checksum = pUtils->calculateCheckSum(*packet);
  return packet;
}

void GBNRdtSender::slide(const Packet &ackPkt) {
  base = (ackPkt.acknum + 1) % seqLength;
  if (base == nextSeqNum && state != START)
    state = FINISH;
}

void GBNRdtSender::goBackN() {
  for (auto &pck : packetWaitingAck) {
#ifdef MUTI_TIMER
    pns->startTimer(SENDER, Configuration::TIME_OUT, pck->seqnum);
#endif
    pns->sendToNetworkLayer(RECEIVER, *pck);
  }
}

void GBNRdtSender::removePacket() {
  auto pred = [this](shared_ptr<Packet> p) { return orderMapping(p->seqnum) < 0; };
  auto it_b = remove_if(packetWaitingAck.begin(), packetWaitingAck.end(), pred);
  packetWaitingAck.erase(it_b, packetWaitingAck.end());
}

bool GBNRdtSender::getWaitingState() { return state == FULL; }

bool GBNRdtSender::send(const Message &message) {
  if (getWaitingState())
    return false;
  auto pkt = makePacket(message);
  pns->sendToNetworkLayer(RECEIVER, *pkt);
  pUtils->printPacket("发送方发送报文", *pkt);
  packetWaitingAck.push_back(pkt);

// 一个定时器
#ifndef MUTI_TIMER
  if (state == START || state == FINISH) {
    state = TRANSPORT;
    pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
#endif
  state = TRANSPORT;

// 多个定时器
#ifdef MUTI_TIMER
  pns->startTimer(SENDER, Configuration::TIME_OUT, pkt->seqnum);
#endif  

  nextSeqNum = (nextSeqNum + 1) % seqLength;
  printSlideWindow();
  if (orderMapping(nextSeqNum) == -winSize)
    state = FULL;
  return true;
}

void GBNRdtSender::receive(const Packet &ackPkt) {
  int checkSum = pUtils->calculateCheckSum(ackPkt);

  //如果校验和正确，并且确认序号在base之后的ack包则被正确接受，同时重启计时器
  if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) >= 0) {
    pUtils->printPacket("发送方正确收到确认", ackPkt);
// 一个定时器
#ifndef MUTI_TIMER
    pns->stopTimer(SENDER, base);
#endif
// 多个定时器
#ifdef MUTI_TIMER
    pns->stopTimer(SENDER, ackPkt.acknum);
#endif
    state = TRANSPORT;
    slide(ackPkt);
#ifndef MUTI_TIMER
    if (state != FINISH) {
      pns->startTimer(SENDER, Configuration::TIME_OUT, base);
    }
#endif
    removePacket();
    printSlideWindow();
  }
}

void GBNRdtSender::timeoutHandler(int seqNum) {
// 一个定时器
#ifndef MUTI_TIMER
  for (auto &pkt : packetWaitingAck) {
    pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *pkt);
  }
  pns->stopTimer(SENDER, base);
  pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  goBackN();
#endif

//多个定时器
#ifdef MUTI_TIMER
  for (auto &pkt : packetWaitingAck) {
    pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *pkt);
    pns->stopTimer(SENDER, pkt->seqnum);
  }
  goBackN();
#endif
}