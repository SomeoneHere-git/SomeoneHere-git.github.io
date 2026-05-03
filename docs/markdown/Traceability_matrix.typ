// Theme
#let theme-bg = rgb("#1a1a1a")
#let theme-fg = rgb("#eeeeee")
#let theme-accent = orange

#set page(fill: theme-bg)
#set text(fill: theme-fg, font: "Linux Libertine")
#show heading: set text(fill: theme-accent)

#import "./functional_requirements.typ": thing

#let UseCase = range(1, 7).map(i => "UC-" + str(i))
#let Sequnce = range(1, 10)
#let Classes = (
  "User",
  "Admin",
  "Team",
  "Task",
  "Timer",
  "NotificationService",
  "MediaSettings",
)


#let Things = thing.map(((id, val, pr)) => id).zip(UseCase, Sequnce).map(((v, v1, v3)) => (v, v1, [], v3))
#table(
  columns: (auto, auto, auto, auto),
  [req], [Use Case], [Class], [Sequnce],
  ..for (v, v1, v2, v3) in Things {
    ([#v], [#v1], [#v2], [#v3])
  },
)
