# 调用关系

## Sender

### send

1. 判断窗口是否满了

2. 制作包
    - makePacket

3. 暂存数据包

4. 发送到网络层
    - API send to network
    - API startTimer

5. 更新窗口状态


### receive
1. 通过Ack包是否损毁来接受确认
    - API checksum

2. 暂存Ack包，通过与base对比能否提交Ack
    - slideWindow
    - removeDataPacket
    - removeAckPacket
    - stopTimer


### timeoutHandler
1. 计时器停止
    - API stopTimer

2. 重传超时的包
    - API send to network
    - API startTimer

### getWaitingState
1. 判断窗口是否满

## Receiver

### receive
1. 判断数据包是否损毁来发出确认
    - API checkSum

3. 发送Ack
    - makePacket
    - API send to network

4. 暂存数据包，通过与base对比尝试交付数据
    - slideWindow
    - removeDataPacket
    - API deliver to app

5. 更新接受状态