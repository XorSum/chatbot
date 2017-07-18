# 能够使用udp协议通信的聊天机器人

这个聊天机器人是用TensorFlow实现的sequence to sequence生成模型，fork自[https://github.com/qhduan/Seq2Seq_Chatbot_QA](https://github.com/qhduan/Seq2Seq_Chatbot_QA)。我添加了使用udp协议于其它程序通信的功能,和一个自动下载解压生成数据库的脚本

## 使用说明

### 第一步 下载数据包

``` bash 
./download.sh
```

这个脚本首先从[这里](https://raw.githubusercontent.com/rustch3n/dgk_lost_conv/master/)下载一份dgk_shooter_min.conv.zip，然后解压出来dgk_shooter_min.conv文件，随后会生成一个sqlite3格式的数据库文件在db/conversation.db，最后会生成一个bucket_dbs目录，里面包含了多个sqlite3格式的数据库，这是将数据按照大小分到不同的buckets里面，例如问题ask的长度小于等于5，并且，输出答案answer长度小于15，就会被放到bucket_5_15_db里面

### 第二步 训练

下面的参数仅仅为了测试，训练次数不多，不会训练出一个好的模型

size: 每层LSTM神经元数量

num_layers: 层数

num_epoch: 训练多少轮（回合）

num_per_epoch: 每轮（回合）训练多少样本

具体参数含义可以参考train.py

输入：`./start.sh`上面这个脚本内容相当于运行：

``` bash
python3 s2s.py \
--size 1024 \
--num_layers 2 \
--num_epoch 5 \
--batch_size 64 \
--num_per_epoch 500000 \
--model_dir ./model/model1
```

输出：在 model/model1 目录会输出模型文件，上面的参数大概会生成700MB的模型

如果是GPU训练，尤其用的是<=4GB显存的显卡，很可能OOM(Out Of Memory)， 这个时候就只能调小size，num_layers和batch_size

### 第三步 测试

下面的测试参数应该和上面的训练参数一样，只是最后加了--test true 进入测试模式

输入：`./start.sh test` 上面这个脚本命令相当于运行：

``` bash
python3 s2s.py \
--size 1024 \
--num_layers 2 \
--num_epoch 5 \
--batch_size 64 \
--num_per_epoch 500000 \
--model_dir ./model/model1 \
--test true
```
输出：在命令行输入问题，机器人就会回答哦！但是上面这个模型会回答的不是很好……当然可能怎么训练都不是很好，不要太期待～～

很多论文进行 bleu 测试，这个本来是测试翻译模型的，其实对于对话没什么太大意义

不过如果想要，可以加 bleu 参数进行测试，例如`./train_model.sh bleu 1000`
具体可以参考 s2s.py 里面的 test_bleu 函数

### 第四步 开启服务

下面的测试参数应该和上面的训练参数一样，只是最后加了--serve true 进入测试模式

输入：`./start.sh serve` 上面这个脚本命令相当于运行：

``` bash
python3 s2s.py \
--size 1024 \
--num_layers 2 \
--num_epoch 5 \
--batch_size 64 \
--num_per_epoch 500000 \
--model_dir ./model/model1 \
--serve true \
--port 8082
```
其中port为端口号

机器人就会使用udp协议绑定8082端口，应当接收到一个字符串并返回一个字符串，分别是用户的问题和机器人的回答
`python3 client.py`会开启一个简易的客户端，可以用于测试通信是否正常
