#include "GBNRdtSender.h"
#include "Global.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

void GBNRdtSender::printSlideWindow() const {
  cout << "######滑动窗口 [base, nextSeqnum]:";
  cout << '[' << base << ',' << nextSeqNum << "] === { ";
  int count = 0;
  for(auto& pkt: packetWaitingAck) {
    cout << pkt->seqnum << ' ';
    count++;
  }
  while(count++ < seqLength) {
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

void GBNRdtSender::slideWindow(const Packet &ackPkt) {
  base = (ackPkt.acknum + 1) % seqLength;
  if (base == nextSeqNum && state != START)
    state = FINISH;
}

void GBNRdtSender::goBackN() {
  for (auto &pck : packetWaitingAck) {
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
  if (state == START || state == FINISH) {
    state = TRANSPORT;
    pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
  nextSeqNum = (nextSeqNum + 1) % seqLength;
  printSlideWindow();
  if (nextSeqNum == base)
    state = FULL;
  return true;
}

void GBNRdtSender::receive(const Packet &ackPkt) {
  int checkSum = pUtils->calculateCheckSum(ackPkt);

  //如果校验和正确，并且确认序号在base之后的ack包则被正确接受，同时重启计时器
  if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) >= 0) {
    pUtils->printPacket("发送方正确收到确认", ackPkt);
    pns->stopTimer(SENDER, base);
    slideWindow(ackPkt);
    removePacket();
    printSlideWindow();
    if (state != FINISH)
      pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
}

void GBNRdtSender::timeoutHandler(int seqNum) {
  for(auto& pkt:packetWaitingAck){
    pUtils->printPacket("发送方定时器时间到，重发上次发送的报文", *pkt);
  }
  pns->stopTimer(SENDER, base);
  pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  goBackN();
}