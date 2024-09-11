#include <iostream>
#include <queue>
#include <vector>

using hp = long long; // 声明血量的类型别名
using hp_pair = std::pair<long long, long long>; // 声明血量信息类型，first是当前血量，second是初始血量

/// 黑塔攻击
///
/// 考虑到输入可能会很大，方法里大多数数值变量都使用了 long long 类型
/// 
/// @param enemy_hp_vector 一组敌人的血量
/// @return 最小普攻次数
long long minimum_normal_attack(std::vector<hp> enemy_hp_vector) {
    long long normal_attack_count = 0; // 普攻次数
    const unsigned enemy_count = enemy_hp_vector.size(); // 敌人总数

    std::vector<hp_pair> enemies;
    enemies.reserve(enemy_count);
    for (int i = 0; i < enemy_count; ++i) {
        enemies.emplace_back(enemy_hp_vector[i], enemy_hp_vector[i]);
    }

    long long aoe_attack = 0; // 已触发的 AOE 攻击次数

    for (int i = 0; i < enemy_count; ++i) {
        auto &[current_health, maximum_health] = enemies[i];
        if (maximum_health <= enemy_count) continue;

        // 如果敌人初始血量大于敌人总数，这些敌人迟早要用普攻打，所以提前进行普攻，更早触发黑塔转圈
        normal_attack_count += maximum_health - enemy_count;
        current_health = enemy_count;
        if (enemy_count <= maximum_health / 2) aoe_attack++;
    }

    // 比较两个敌人谁的当前血量更接近半血，假设传入血量不会存在已经小于半血的情况
    auto compare = [](const hp_pair &a, const hp_pair &b) {
        return a.first - a.second / 2 > b.first - b.second / 2;
    };

    // 虽然可以直接在vector里排序，但compare就要考虑血量已经小于半血的情况
    // 这里使用优先队列来实现取出当前血量最接近半血的敌人
    std::priority_queue<hp_pair, std::vector<hp_pair>, decltype(compare)> pq(compare);
    for (int i = 0; i < enemy_count; ++i) {
        if (enemies[i].first > enemies[i].second / 2) pq.push(enemies[i]);
    }

    while (!pq.empty()) {
        auto [enemy_current_hp, enemy_maximum_hp] = pq.top(); // 每次取出当前血量最接近半血的敌人
        pq.pop();
        // 考虑已经触发过的 AOE 能否把这个敌人的血量打到初始值一半以下，如果不能，就用普攻打到能够打出 AOE 为止
        if (enemy_current_hp - aoe_attack > enemy_maximum_hp / 2) {
            normal_attack_count += enemy_current_hp - enemy_maximum_hp / 2 - aoe_attack;
        }
        ++aoe_attack;
        // 不考虑剩余血量，只要所有 AOE 都触发了，剩余血量就会被打掉
    }

    return normal_attack_count;
}

int main() {
    std::vector<std::pair<hp, std::vector<hp> > > cases = {
        {7, {5, 6}},
        {1, {1, 2, 3, 4, 5}},
        {3, {1, 3, 6}},
        {6, {5, 5, 5, 5, 5}},
    };
    for (auto &[want, enemy_health]: cases) {
        if (const long long got = minimum_normal_attack(enemy_health); got != want) {
            std::cerr << "预期普通次数是" << want << "但得到的普攻次数是" << got << std::endl;
            return 1;
        }
    }
    std::cout << "ac" << std::endl;
    return 0;
}
