# herta_attack_puzzle

> [黑塔转圈圈问题 - 力扣](https://leetcode.cn/circle/discuss/hrR0Gy/)

## 题目

黑塔女士的普通攻击可以对一名敌人造成一点伤害。此外，黑塔女士的天赋，会在敌人的生命值首次降低到初始值的二分之一（向下取整）时，立即发动追加攻击，对所有敌人造成一点伤害。

追加攻击造成的伤害可以继续触发追加攻击，且多个敌人的生命值同时下降到二分之一时，每个敌人都可以触发一次追加攻击。

现在有许多敌人，黑塔女士应该如何用最少的普通攻击消灭所有敌人呢？

## 输入格式

### 输入

一个长度为 `n` 整数数组 `a`， 表示有 `n` 名敌人，第 `i` 名敌人初始生命值为 `a[i]`。

$0<n<10^5$, $0<a_i<10^9$

### 输出

一个整数，表示消灭所有敌人最少需要的普通攻击次数。

## 示例

```text
[5, 6]
7    // 需要普通攻击0号敌人3次，1号敌人4次。
[1, 2, 3, 4, 5]
1    // 对0号敌人或者对1号敌人进行一次普通攻击即可。
[1, 3, 6]
3    // 对初始生命为6的敌人进行3次普通攻击即可。
```