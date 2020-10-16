#ifndef PACKET_SORT_H
#define PACKET_SORT_H
#include "Global.h"
#include <algorithm>
#include <memory>
#include <vector>
using std::pair;
using std::shared_ptr;
using std::vector;

class PacketSort final{
private:
  class PacketComp {
    bool operator()(pair<shared_ptr<Packet>, int> &pkt1, pair<shared_ptr<Packet>, int> &pkt2);
  };
  static PacketComp comp;
public:
  static void sort(vector<pair<shared_ptr<Packet>, int>> &vec);
  PacketSort() = delete;
};
#endif