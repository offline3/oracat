# SSH基本用法

## 1  简介

SSH（Secure Shell）是建立在应用层基础上的安全网络协议。SSH主要用于不同机器之间的通讯。SSH是基于Client-Server架构，包含ssh-client和ssh-server两部分。linux环境中，通常使用开源的openssh, 安装方法如下（以ubuntu为例）：
服务端安装：

```bash
sudo apt-get install openssh-server
```
客户端安装：
```bash
sudo apt-get install openssh-client
```
启动/查看ssh服务：
```bash
service ssh start
service ssh status
```
可以通过ps命令查看ssh服务是否开启，软件以d结尾（sshd）表示守护进程（deamon）：
```bash
ps -e | grep sshd
```
ssh提供两种级别的验证方式。
- 基于口令的安全验证：需要直到目标机器人的帐号和口令，就可以登录到远程目标主机；所有传输的数据都会被加密，但是不能保证你正在连接的服务器就是你想连接的服务器。可能会有别的服务器在冒充真正的服务器，也就是受到“中间人攻击”这种方式的攻击。
- 基于密钥的安全验证：需要创建一对密钥，并把公钥放在需要访问的服务器上。如果你要连接到SSH服务器上，客户端软件就会向服务器发出请求，请求用你的密钥进行安全验证。服务器收到请求之后，先在该服务器上你的主目录下寻找你的公钥，然后把它和你发送过来的公钥进行比较。如果两个密钥一致，服务器就用公钥加密“质询”(challenge)并把它发送给客户端软件。客户端软件收到“质询”之后就可以用你的私钥在本地解密再把它发送给服务器完成登录。与第一种级别相比，第二种级别不仅加密所有传输的数据，也不需要在网络上传送口令，因此安全性更高，可以有效防止中间人攻击。

## 2 登入远程主机

要通过从本机登入到远程主机，本机需要安装ssh-client，而远程主机需要开启ssh-server服务

### 基于口令形式

基于口令形式需要知道远程主机的登入密码，命令如下：
```bash
ssh user@remote -p port
```
- user 是你在远程机器上的用户名，如果不指定的话默认为当前用户
- remote 是远程机器的地址，可以是 IP，域名，或者是后面会提到的别名
- port 是 SSH Server 监听的端口，如果不指定的话就为默认值 22

输入远程主机密码之后便可以从本机登入到远程主机

### 基于密匙形式

基于密匙形式需要创建一对密匙，ssh创建密匙方式如下，连续三次回车键：
```bash
ssh-keygen -t rsa -C <comment>
```
- \-t 指密匙类型
- \-C 指密匙注释，可以省略

在执行上述命令之后，ssh会生成一对密匙，公钥放在 ~/.ssh/id_rsa.pub，私钥放在了 ~/.ssh/id_rsa。

生成密匙之后，便可以让远程主机记住我们的公钥。在本机上输入下述命令：

```bash
ssh-copy-id user@remote -p port
```
若没有ssh-copy-id，可以通过以下命令：
```bash
ssh user@remote -p port 'mkdir -p .ssh && cat >> .ssh/authorized_keys' < ~/.ssh/id_rsa.pub
```
这段命令的含义是在远程主机执行命令
```bash
mkdir -p .ssh && cat >> .ssh/authorized_keys
```
通过输入重定向，将本机~/.ssh/id_rsa.pub内容输入到远程主机.ssh/authorized_keys下。

若要删除本机密匙，只需删除~/.ssh文件
```bash
rm -rf ~/.ssh
```
若要在远程主机要删除本机的公钥，在远程主机执行命令
```bash
ssh-keygen -R local-hostname
```


## 3 配置远程主机别名

通过配置远程主机别名可以简化命令行，如要通过vm别名代替user@remote -p port，首先在~/.ssh/config里追加以下内容：
```
Host vm
    HostName remote
    User user
    Port port
```
之后便可以通过下述命令登入主机：
```bash
ssh vm
```

## 4 文件传输

不同主机之间可以通过scp进行文件传输，如要传输文件夹，可以使用**scp -r**命令；如把本地的 /path/to/local/file 文件传输到远程的 /path/to/remote/file
```bash
scp /path/to/local/file user@remote:/path/to/remote/file
```
把远程的 /path/to/remote/file 下载到本地的 /path/to/local/file
```bash
scp user@remote:/path/to/remote/file /path/to/local/file