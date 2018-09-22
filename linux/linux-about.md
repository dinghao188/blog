# Linux和操作系统的相关知识记录

## linux的设计理念和艺术

1. linux中一切都是文件，通俗来说就是将不同的设备，如鼠标，键盘，屏幕，硬盘等统统都组织成文件的形式，这些文件都是块设备文件，通过对文件的操作完成对设备的访问，这是一种实现单设备多进程共享的极佳方式。

2. linux中的回环设备（loopback device）是一个非常重要的概念，任何设备文件或者是虚拟文件都可与一个回环设备产生关联，通过操作回环设备就能完成对文件本身的操作，下面是一些经典的使用方式：

```b
    以下操作均已超级用户的身份进行：
    losetup /dev/loopXXX filepath   产生一个/dev目录下的名为loopXXX的回环设备文件与filepath文件进行关联
    losetup -d /dev/loopXXX     删除一个名为loopXXX的回环设备
    如果某个回环设备loopX关联了一个虚拟的磁盘文件，则可以通过使用fdisk对其进行分区，然后使用kpartx将其分区映射到/dev/mapper/loopXpX,通过操作loopXpX就可以完成对虚拟磁盘特定分区的格式化操作。基本操作：
    kpartx -av /dev/loopX   生成映射
    kpartx -dv /dev/loopX   删除映射
```
