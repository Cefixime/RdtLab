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

void GBNRdtSender::setSeqNum(int len) { seqLength = len; }

Packet *GBNRdtSender::makePacket(const Message &message) {
    auto packet = new Packet();
    packet->acknum = -1;
    packet->seqnum = nextSeqNum;
    packet->checksum = 0;
    memcpy(packet->payload, message.data, sizeof(message.data));
    packet->checksum = pUtils->calculateCheckSum(*packet);
    return packet;
}

void GBNRdtSender::slideWindow(const Packet &ackPkt) { base = ackPkt.acknum + 1; }

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

bool GBNRdtSender::getWaitingState() { return orderMapping(nextSeqNum) <= seqLength; }

bool GBNRdtSender::send(const Message &message) {
    if (getWaitingState())
        return false;
	auto pck = makePacket(message);
	pns->sendToNetworkLayer(RECEIVER, *pck);
	if(base == nextSeqNum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, base);
	// TODO: 更新窗口状态
}