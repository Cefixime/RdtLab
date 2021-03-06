// SR.cpp : 定义控制台应用程序的入口点。
//


#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "SRRdtSender.h"
#include "SRRdtReceiver.h"


int main(int argc, char* argv[])
{
  auto srs = new SRRdtSender();
  // srs->setSeqLength(16);
  // srs->setWinSize(8);
	RdtSender *ps = srs;
  auto srr = new SRRdtReceiver();
  // srr->setSeqLength(16);
	RdtReceiver * pr = srr;
	pns->setRunMode(0);  //VERBOS模式
	// pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("/home/wei/workspace/NetWorkLab/RdtLab/input.txt");
	pns->setOutputFile("/home/wei/workspace/NetWorkLab/RdtLab/output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;									//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;										//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}

