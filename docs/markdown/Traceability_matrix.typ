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
  columns: (auto, auto, 2fr, auto),
  inset: 10pt,
  [*ID*], [*Use Case*], [*Classes*], [*Sequence*],
  [FR-1], [UC01, UC07], [Admin, User, Team], [--],
  [FR-2], [UC06], [User, Task], [SD-02],
  [FR-3], [UC08, UC04], [User, Admin], [SD-02],
  [FR-4], [UC09], [MediaSettings], [--],
  [FR-5], [UC11], [NotificationService, Task, Timer], [--],
  [FR-6], [UC05, UC02], [Timer, Task], [SD-02],
  [FR-7], [UC03], [Task], [SD-02],
)
