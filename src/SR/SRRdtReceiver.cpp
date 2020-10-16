#include "SRRdtReceiver.h"
#include "Global.h"
#include "PacketSort.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

shared_ptr<Packet> SRRdtReceiver::makePacket(int seqNum) {
  shared_ptr<Packet> pkt = make_shared<Packet>();
  pkt->acknum = seqNum;
  pkt->seqnum = -1;
  for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
    pkt->payload[i] = '.';
  }
  pkt->checksum = pUtils->calculateCheckSum(*pkt);
  return pkt;
}

void SRRdtReceiver::slide(const Packet &ackPkt) {
  int shift = 1;
  for (auto &pkt : waitingDeliverPkt) {
    if (pkt.second == shift)
      shift++;
    else
      break;
  }
  base = (base + shift) % seqLength;
  for (auto &pkt : waitingDeliverPkt) {
    pkt.second -= shift;
  }
}

void SRRdtReceiver::removeDataPacket() {
  auto pred = [this](const pair<shared_ptr<Packet>, int> &pkt) { return pkt.second < 0; };
  auto it_b = remove_if(waitingDeliverPkt.begin(), waitingDeliverPkt.end(), pred);
  waitingDeliverPkt.erase(it_b, waitingDeliverPkt.end());
}

void SRRdtReceiver::deliverPacket() {
  int index = 1;
  for (auto &packet : waitingDeliverPkt) {
    if (packet.second != index)
      break;
    Message msg;
    memcpy(msg.data, packet.first->payload, sizeof(packet.first->payload));
    pns->delivertoAppLayer(RECEIVER, msg);
    index++;
  }
}
void SRRdtReceiver::printSlideWindow() const {
  cout << "######滑动窗口 [base]:";
  cout << '[' << base << "] === { ";
  int index = 0;
  auto it = waitingDeliverPkt.cbegin();
  auto it_end = waitingDeliverPkt.cend();
  while (index < winSize) {
    if (it != it_end && it->second == index) {
      cout << it->first->seqnum << ' ';
      it++;
    } else
      cout << "@ ";
    index++;
  }
  cout << "}\n";
}

void SRRdtReceiver::receive(const Packet &packet) {
  int checkSum = pUtils->calculateCheckSum(packet);
  if (checkSum == packet.checksum) {
    auto ackPkt = makePacket(packet.seqnum);
    int seqNum = packet.seqnum;
    auto pred = [this, seqNum](const pair<shared_ptr<Packet>, int> &pkt) { return pkt.first->seqnum == seqNum; };
    auto pkt = find_if(waitingDeliverPkt.cbegin(), waitingDeliverPkt.cend(), pred);
    if (orderMapping(seqNum) >= 0 && pkt == waitingDeliverPkt.cend()) {
      pUtils->printPacket("接收方正确收到发送方的报文", packet);
      if (seqNum == base) {
        // 取出Message，向上递交给应用层
        Message msg;
        memcpy(msg.data, packet.payload, sizeof(packet.payload));
        pns->delivertoAppLayer(RECEIVER, msg);
        deliverPacket(); // 交付暂存的其他可交付数据
        slide(packet);   // 滑动窗口
        removeDataPacket();
      } else {
        // 暂存失序的数据包
        auto dataPkt = make_shared<Packet>(packet);
        waitingDeliverPkt.push_back(make_pair(dataPkt, orderMapping(dataPkt->seqnum)));
        PacketSort::sort(waitingDeliverPkt);
      }
      printSlideWindow(); // 显示当前的窗口
      pUtils->printPacket("接收方发送确认报文", *ackPkt);
      //调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
      pns->sendToNetworkLayer(SENDER, *ackPkt);
    } else {
      pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
      pUtils->printPacket("接收方重新发送该确认报文", *ackPkt);
      pns->sendToNetworkLayer(SENDER, *ackPkt); //调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文
    }
  } else {
    pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
  }
}