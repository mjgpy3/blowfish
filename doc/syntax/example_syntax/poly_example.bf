module CarStuff [

  class Car [
    meth new withName: name andId: id[
      self.name = name
      self.id = id
    ]
  ]

  forms Car are Toyota | Honda

  class Toyota [
    meth is_made_in_the_usa [
      return False
    ]
  ]

  a := Toyota.new withName: "4runner" andId: 1

  if a.is_made_in_the_usa [
    say "Yep, it's made in the USA"
  ]
]
