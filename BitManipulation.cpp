【位操作实现四则运算】
常见功能的位操作实现，具体为：

<1> 常用的等式：-n = ~(n-1) = ~n+1

<2> 获取整数n的二进制中最后一个1：n&(-n) 或者 n&~(n-1)，如：n=010100，则-n=101100，n&(-n)=000100

<3> 去掉整数n的二进制中最后一个1：n&(n-1)，如：n=010100，n-1=010011，n&(n-1)=010000
（1） 加法实现

可以很容易地用“异或”和“或”操作实现整数加法运算：对应位数的“异或操作”可得到该位的数值，对应位的“与操作”可得到该位产生的高位进位，如：a=010010，b=100111，计算步骤如下：

第一轮：a^b=110101，(a&b)<<1=000100， 由于进位（000100）大于0，则进入下一轮计算，a=110101，b=000100，a^b=110001，(a&b)<<1=001000，由于进位大于0，则进入下一轮计算：a=110001，b=001000，a^b=111001，(a&b)<<1=0，进位为0，终止，计算结果为：111001。

int add(int a, int b) {
  int carry, add;
  do {
    add = a ^ b;
    carry = (a & b) << 1;
    a = add;
    b = carry;
  } while(carry != 0);
  return add;
}
（2） 减法实现

减法可很容易地转化为加法：a - b = a + (-b) = a + (~b + 1 )

代码如下：

int subtract(int a, int b) {
  return add(a, add(~b, 1));
}
（3） 乘法实现
先看一个实例：1011*1010：

1011
   * 1010
 ----------
    10110 < 左移一位，乘以0010
+ 1011000 < 左移3位，乘以1000
----------
  1101110
因而乘法可以通过系列移位和加法完成。最后一个1可通过b&~(b-1)求得，可通过b& (b-1)去掉，为了高效地得到左移的位数，可提前计算一个map，代码如下：
int multiply(int a, int b) {
  bool neg = (b < 0);
  if(b < 0)
    b = -b;
  int sum = 0;
  map<int, int> bit_map;
  for(int i = 0; i < 32; i++)
    bit_map.insert(pair<int, int>(1 << i, i));
    while(b > 0) {
      int last_bit = bit_map[b & ~(b - 1)];
      sum += (a << last_bit);
      b &= b - 1;
    }
  if(neg)
    sum = -sum;
  return sum;
}
（4） 除法实现
乘法可很容易转化为减法操作，主要思想与乘法实现类似，代码如下：
int divide(int a, int b) {
  bool neg = (a > 0) ^ (b > 0);
  if(a < 0)
    a = -a;
  if(b < 0)
    b = -b;
  if(a < b)
    return 0;
  int msb = 0;
  for(msb = 0; msb < 32; msb++) {
    if((b << msb) >= a)
      break;
  }
  int q = 0;
  for(int i = msb; i >= 0; i--) {
    if((b << i) > a)
      continue;
    q |= (1 << i);
    a -= (b << i);
  }
  if(neg)
    return -q;
  return q;
}
