# 调用关系

## Sender

### send

1. 判断窗口是否满了

2. 制作包
    - makePacket

3. 发送到网络层
    - API send to network

4. 传输开始时需要启动计时器
    - API startTimer

5. 更新窗口状态


### receive
1. 通过Ack包是否损毁来接受确认
    - API checksum
    - slideWindow
    - removePacket
    - API startTimer
2. 否则什么也不做

3. 判断是否传输结束
    - API stopTimer
### timeoutHandler
1. 计时器更新
    - API stopTimer
    - API startTimer

2. 重传队列中的包
    - goBackN
        - API send to network

### getWaitingState
1. 判断窗口是否满

## Receiver

### receive
1. 判断数据包是否损毁来发出确认
    - API deliver to app
    - makePacket
    - API send to network

2. 更新接受状态