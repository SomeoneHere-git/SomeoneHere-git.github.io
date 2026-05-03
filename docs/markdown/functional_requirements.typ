// Theme
#let theme-bg = rgb("#1a1a1a")
#let theme-fg = rgb("#eeeeee")
#let theme-accent = orange

#set page(fill: theme-bg)
#set text(fill: theme-fg, font: "Linux Libertine")
#show heading: set text(fill: theme-accent)

#let REQ_NUMBERS = 7
#let Req = (
  [  Система має дозволяти адміністратору додавати/видаляти нових користувачів в команду],
  [  Система має дозволяти користувачам підписуватись на завдання],
  [  Система має дозволяти реєєструватись через email],
  [  Система має дозволяти вибирати музику],
  [  Система має автоматично повідомляти що строк завдання закінчився],
  [  Система має автоматично оновлювати час завдання],
  [  Система має дозволяти користувачам змінювати стан завдання],
)
#let prior = (
  [1],
  [1],
  [1],
  [3],
  [2],
  [2],
  [1],
)
#let thing = range(1, 7 + 1).map(i => "FR-" + str(i)).zip(Req, prior)

#table(
  columns: (auto, auto, auto),
  [*ID*], [req], [priority],

  ..for (id, val, pr) in thing {
    (
      [#id],
      [#val],
      [#pr],
    )
  },
)
