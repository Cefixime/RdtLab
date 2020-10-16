#include "Global.h"
#include "PacketSort.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

void PacketSort::sort(vector<pair<shared_ptr<Packet>, int>> &vec) {
  std::sort(vec.begin(), vec.end(), comp);
}

bool PacketSort::PacketComp::operator()(pair<shared_ptr<Packet>, int> &pkt1, pair<shared_ptr<Packet>, int> &pkt2) {
  return pkt1.second < pkt2.second;
}