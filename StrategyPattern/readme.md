# Strategy Pattern

適用時機：不同 class 之間有相同的 function

透過在 base class 加入 behavior 的 base class 來記錄要執行的 function 物件

1. reuse the same function in different class(將在不同 class 中卻相同的行為包成一個 class)
2. allow update behavior in execution time(function 物件化後，可以透過換物件來達成執行期改 function)

## example
實作五種鴨子，五種鴨子有各自的叫聲以及飛行行為，其中叫聲和行為可能重複
MallarDuck: quack, fly
RedHeadDuck: quack, fly
RubberDuck: squack, nofly
WoodenDuck: mute, nofly
RobotDuck: bibo, fly

RobotDuck 在執行期，可以透過火箭來飛