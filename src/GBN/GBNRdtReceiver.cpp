#include "GBNRdtReceiver.h"
#include "Global.h"
#include "SlideWindow.h"
#include <memory>
using namespace std;

GBNRdtReceiver::GBNRdtReceiver() : expectSequenceNumberRcvd(0), seqLen(SEQ_LEN) {
  lastAckPkt = makePacket(SEQ_LEN - 1);
}

shared_ptr<Packet> GBNRdtReceiver::makePacket(int seqNum) {
  shared_ptr<Packet> pkt = make_shared<Packet>();
  pkt->acknum = seqNum;
  pkt->seqnum = -1;
  for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
    pkt->payload[i] = '.';
  }
  pkt->checksum = pUtils->calculateCheckSum(*pkt);
  return pkt;
}

void GBNRdtReceiver::receive(const Packet &packet) {
  int checkSum = pUtils->calculateCheckSum(packet);
  if (checkSum == packet.checksum && packet.seqnum == expectSequenceNumberRcvd) {
    pUtils->printPacket("接收方正确收到发送方的报文", packet);
    //取出Message，向上递交给应用层
    Message msg;
    memcpy(msg.data, packet.payload, sizeof(packet.payload));
    pns->delivertoAppLayer(RECEIVER, msg);
    lastAckPkt = makePacket(expectSequenceNumberRcvd);
    pUtils->printPacket("接收方发送确认报文", *lastAckPkt);
    //调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
    pns->sendToNetworkLayer(SENDER, *lastAckPkt);
    expectSequenceNumberRcvd = (expectSequenceNumberRcvd + 1) % seqLen;
  } else {
    if (checkSum != packet.checksum) {
      pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
    } else {
      pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
    }
    pUtils->printPacket("接收方重新发送上次的确认报文", *lastAckPkt);
    pns->sendToNetworkLayer(SENDER, *lastAckPkt); //调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文
  }
}