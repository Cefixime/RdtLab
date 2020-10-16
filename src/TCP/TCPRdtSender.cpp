#include "TCPRdtSender.h"
#include "Global.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

void TCPRdtSender::printSlideWindow() const {
  cout << "######发送方滑动窗口 [base, nextSeqnum]:";
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

shared_ptr<Packet> TCPRdtSender::makePacket(const Message &message) {
  shared_ptr<Packet> packet = make_shared<Packet>();
  packet->acknum = -1;
  packet->seqnum = nextSeqNum;
  packet->checksum = 0;
  memcpy(packet->payload, message.data, sizeof(message.data));
  packet->checksum = pUtils->calculateCheckSum(*packet);
  return packet;
}

void TCPRdtSender::slide(const Packet &ackPkt) {
  base = (ackPkt.acknum + 1) % seqLength;
  if (base == nextSeqNum && state != START)
    state = FINISH;
}

void TCPRdtSender::removePacket() {
  auto pred = [this](shared_ptr<Packet> p) { return orderMapping(p->seqnum) < 0; };
  auto it_b = remove_if(packetWaitingAck.begin(), packetWaitingAck.end(), pred);
  packetWaitingAck.erase(it_b, packetWaitingAck.end());
}

bool TCPRdtSender::getWaitingState() { return state == FULL; }

bool TCPRdtSender::send(const Message &message) {
  if (getWaitingState())
    return false;
  auto pkt = makePacket(message);
  pns->sendToNetworkLayer(RECEIVER, *pkt);
  pUtils->printPacket("发送方发送报文", *pkt);
  packetWaitingAck.push_back(pkt);
  if (state == START || state == FINISH) {
    state = TRANSPORT;
    pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
  nextSeqNum = (nextSeqNum + 1) % seqLength;
  printSlideWindow();
  if (orderMapping(nextSeqNum) == -winSize)
    state = FULL;
  return true;
}

void TCPRdtSender::receive(const Packet &ackPkt) {
  if (state == FINISH)
    return;
  int checkSum = pUtils->calculateCheckSum(ackPkt);

  //如果校验和正确，并且确认序号在base之后的ack包则被正确接受，同时重启计时器
  if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) >= 0) {
    pUtils->printPacket("发送方正确收到确认", ackPkt);
    ackRedundant = 0;
    pns->stopTimer(SENDER, base);
    state = TRANSPORT;
    slide(ackPkt);
    if (state != FINISH) {
      pns->startTimer(SENDER, Configuration::TIME_OUT, base);
    }
    removePacket();
    printSlideWindow();
  } else if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) == -1) {
    pUtils->printPacket("发送方收到冗余的确认", ackPkt);
    ackRedundant++;
    if (ackRedundant == 2) {
      fastResend();
      ackRedundant = 0;
    }
  }
}

void TCPRdtSender::timeoutHandler(int seqNum) {
  pUtils->printPacket("发送方定时器时间到，重发最早未确认的报文", *(packetWaitingAck.front()));
  ackRedundant = 0;
  pns->stopTimer(SENDER, base);
  pns->sendToNetworkLayer(RECEIVER, *(packetWaitingAck.front()));
  pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}

void TCPRdtSender::fastResend() {
  pUtils->printPacket("快速重传", *(packetWaitingAck.front()));
  pns->stopTimer(SENDER, base);
  pns->sendToNetworkLayer(RECEIVER, *(packetWaitingAck.front()));
  pns->startTimer(SENDER, Configuration::TIME_OUT, base);
}