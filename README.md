新版本：https://github.com/Jaf932074323/serialize.git

# Serialization-and-Deserialization-Data
对数据对象序列化和反序列化操作

MIT 许可证

编译环境：windows平台下vs2019编译器，C++14标准。ISO C++14 标准。目前没有考虑跨平台的功能。

解决方案中有2个项目，Sdd和SddTest。其中Sdd项目为序列化和反序列化库。SddTest项目为对库的测试。Sdd库项目中，有"TestSdd.h"和"TestPackAndUnpack.h"两个文件是使用demo，可以从中了解用法，同时也可以当做单元测试使用。
这个库不涉及到多线程操作，因此没考虑过同步问题，线程不安全。

业余时间编写的对数据对象序列化和反序列化操作。很久以前就开始编写这个库了。一直在调整内部结构。
主要目的是为了简化组包与拆包工作。在使用网络套接字通讯时，通常会根据通讯协议来将特定的数据组装成字节数据进行发送，另一半接收数据并且拆包还原出数据。如心跳包之类的。很多时候还要考虑大小端序的问题。使用这个库能简化编码功能。

目前想到但还没有完善的地方，后续有时间再来优化：
1.对变长包的支持没有过多考虑，如一个不知道长度的字符串的序列化工作没有实现，只实现了特定长度字符串的序列化。
2.对数组类型的包支持没有考虑。
3.对位的支持不够完善。



