#include "GBNRdtSender.h"
#include "Global.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

int GBNRdtSender::orderMapping(int seqNum) {
  int result = seqNum - base;
  if (result >= 0 && result <= 3)
    return result;
  else if (result > 3)
    return result - 8;
  else if (result < -4)
    return result + seqLength;
  else if (result < 0 && result >= -4)
    return result;
}

void GBNRdtSender::setSeqNum(int len) {
  seqLength = len;
  winSize = len / 2;
}

Packet *GBNRdtSender::makePacket(const Message &message) {
  auto packet = new Packet();
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
  if (state == START) {
    state = TRANSPORT;
    pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
  nextSeqNum = (nextSeqNum + 1) % seqLength;
  if (nextSeqNum == base)
    state = FULL;
}

void GBNRdtSender::receive(const Packet &ackPkt) {
  int checkSum = pUtils->calculateCheckSum(ackPkt);

  //如果校验和正确，并且确认序号在base之后的ack包则被正确接受，同时重启计时器
  if (checkSum == ackPkt.checksum && orderMapping(ackPkt.acknum) >= 0) {
    pns->stopTimer(SENDER, base);
    slideWindow(ackPkt);
    removePacket();
    if (state != FINISH)
      pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  }
}

void GBNRdtSender::timeoutHandler(int seqNum) {
  pns->stopTimer(SENDER, base);
  pns->startTimer(SENDER, Configuration::TIME_OUT, base);
  goBackN();
}