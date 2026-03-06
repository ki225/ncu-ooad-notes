# Exception Safe
Exception Safe 的目的是希望在程式拋出 exception 的時候，程式裡的物件能夠保持狀態一致性，不會破壞資料或資源。也就是說，當 exception 發生時，程式應該仍然維持合理的狀態，不會造成資源洩漏（memory leak）、資料損壞或不一致的狀況。

這就好比說假設我用 ATM 轉帳 1000 元給我朋友，在這場交易中資源只有這一千塊，以正常交易流程來說應該會經過:

1. 扣我的帳戶 1000
2. 加到朋友帳戶 1000

結果在第一步結束時網路斷線了，導致過程變成:

1. 我的帳戶 -1000
2. 朋友帳戶 +0

身上少了這 1000 的我或許就因為餘額不足而沒辦法再進行一千元交易，這樣狀態不一致的狀況其實就解釋了 exception safety 的意義。

因此 exception safety 的目標通常是確保：

- 物件的狀態不會被破壞
- 資源不會遺失
- 程式可以安全地繼續執行或結束

## 範例: Assignment Operator Overloading 可能的問題
在[上一個章節](../4_copy_assignment_operator/README.md) 提到 copy assignment operator 預設其實是做 member-wise copy，若 class 內有 pointer 或需要自行管理資源就可能出現問題，為了解決這個問題我們自行定義了 copy assignment operator，如果沒有特別可慮 exception safe 的話，我們可能會寫:

```c
Foo& Foo::operator=(const Foo& rhs) {
    delete this->bar_;
    this->bar_ = new Bar(*rhs.bar_);
    return *this;
}
```
但執行 `new()` 是有機會失敗的，像是當記憶體不足時就會拋出 exception bad_alloc，這時候就會發生
1. 原本的 `bar_` 已經被刪除
2. 但新的 `bar_` 尚未建立

此時物件會變成不完整或無效的狀態，這就違反了 exception safety。


## 解決方法: copy-and-swap idiom
建立一個 temp 物件，先完成所有可能丟出 exception 的操作。如果過程發生錯誤導致 exception，stack 上的 temp 物件會自動被釋放，而原本的物件不會被改動。
```cpp
Foo& operator=(const Foo& rhs) {
    // copy member, ref: F.47: Return T& from assignment operators
    Foo temp(rhs);              // 先 copy (可能丟 exception)
    std::swap(bar_, temp.bar_); // swap, C++ 確保 swap 不會 exception (除非你自己寫了一個不遵守規則的 swap)
    return *this;
}
```
> ps 如果自己設計 swap 也要確保不會發生 exception

## REF
- [Way to C++: 6. Exception Safe](https://mukyu.medium.com/way-to-c-6-exception-safe-3f44485284af)
- [Copy-and-Swap Idiom in C++](https://www.geeksforgeeks.org/cpp/copy-swap-idiom-c/)
- [[C++] Exception Safety & Guarantees](https://shininglionking.blogspot.com/2014/03/c-exception-safety-guarantees.html)
- [E.16: Destructors, deallocation, swap, and exception type copy/move construction must never fail](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e16-destructors-deallocation-swap-and-exception-type-copymove-construction-must-never-fail)
- [Discussion: Destructors, deallocation, and swap must never fail](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#discussion-destructors-deallocation-and-swap-must-never-fail)