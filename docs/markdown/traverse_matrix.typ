#set page(
  paper: "a4",
  margin: 2cm,
  fill: white,
)
#set text(
  fill: rgb("#1a1a1a"),
  font: "DejaVu Sans",
  size: 11pt,
)

#show heading: set text(fill: rgb("#2d2d2d"))

#align(center)[
  #heading(level: 2)[2.3.5 Матриця трасованості проєкту]
]

#v(1em)


#table(
  columns: (auto, 1fr, 2fr, 1.5fr),
  inset: 10pt,
  align: horizon,
  stroke: 0.5pt + gray,
  fill: (x, y) => if y == 0 { rgb("#f0f0f0") } else { white },

  [*Вимога*], [*Use Case*], [*Класи*], [*Sequence*],

  [FR-01], [UC_Reg], [User], [--],
  [FR-02], [UC_Team], [User, Team], [--],
  [FR-03], [UC_Progress], [User, Task], [SD-01 (Update)],
  [FR-04], [UC_Manage], [TeamLead, User, Team], [--],
  [FR-05], [UC_Music], [User, MusicPlayer], [--],
  [FR-06], [UC_Music], [MusicPlayer], [--],
)

