# Space invaders Overview
## Advanced Programming Lecture

### Programming Language: Golang
#### Team Members :
* Juan Antonio Melendres Villa
* Héctor Eduardo Martínez Alcantara


************************

Space invaders has a empiric based architecture. It consists of one .go files that will be described bellow.

![Space Invaders](space-invaders.png)

[main.go](spaceInvadersWithGoRoutines)
- Main file, it constains all the program, functions and the creation of a Window.

Space Ship Struct - All of the assets we use, are create in this struct, to difference we have the kind that all the kinds are Gun (Main character), Aliens, Bullet (For character), Bomb (For aliens) and Fortress.

```
  type spaceShip struct {
    kind  string
    name  string
    x     float64
    y     float64
    alive bool
    vx    float64
    vy    float64
    in    chan msg
  }
```

Colors - All of the assets we use have a different color to know what is happening in the game Gun = Green, Aliens = Red, Bullet = Orange, Bomb = Blue and Fortress = White.

```
for _, s := range m.register {
  if s.alive && s.kind == "Gun" {
    imd.Color = colornames.Green
    imd.Push(pixel.V(float64(s.x), float64(s.y)))
    imd.Circle(6, 3)
  } else if s.alive && s.kind == "Alien" {
    imd.Color = colornames.Red
    imd.Push(pixel.V(float64(s.x), float64(s.y)))
    imd.Circle(4, 2)
  } else if s.alive && s.kind == "Fortress" {
    imd.Color = colornames.White
    imd.Push(pixel.V(float64(s.x), float64(s.y)))
    imd.Circle(5, 4)
  } else if s.alive && s.kind == "Bullet" {
    imd.Color = colornames.Orange
    imd.Push(pixel.V(float64(s.x), float64(s.y)))
    imd.Circle(2, 2)
  } else if s.alive && s.kind == "Bomb" {
    imd.Color = colornames.Blue
    imd.Push(pixel.V(float64(s.x), float64(s.y)))
    imd.Circle(3, 2)
  }
}
```

Populate function - This function help us to create all the Aliens and fortress, we have the specific size of the window, the aliens have to align with the window, and we have a condition to create the specific aliens, the range of the aliens is between 1 to 48 that is the maximum to add on the screen. For the Fortress we create a matrix 3 x 3 to have a protect our main player.

```
func populate() {
  var spacingPx = 50
  var con = 0
  for r := 0; r < 300/spacingPx; r++ {
    for i := 0; i < 400/spacingPx; i++ {
      if con < numAliens {
        ms.generalChannel <- msg{cmd: "Add", val: "Alien", p: spaceShip{x: float64(100 + spacingPx*i), y: float64(200 + spacingPx*r), vx: float64(-100 + rand.Intn(1)), vy: 0}}
      }
      con++
    }
  }
  for f := 0; f < 3; f++ {
    for c := 0; c < 3; c++ {
      for r := 0; r < 3; r++ {
        ms.generalChannel <- msg{cmd: "Add", val: "Fortress", p: spaceShip{x: float64(100 + f*100 + c*10), y: float64(60 + r*10), vx: 0, vy: 0}}
      }
    }
  }
  ms.generalChannel <- msg{cmd: "Add", val: "Gun", p: spaceShip{x: 100, y: 10, vx: 0, vy: 0}}
}
```

***************************

### Graph

The following graph was used for the Space Invaders

https://raw.githubusercontent.com/Kenshex7/ap-labs/space-invaders/challenges/space-invaders/ArchitectureDiagram.png

### Libraries
- PixelGL

### Space invaders prerequisites:
- Have Golang installed.
- Have libxcursor-dev installed.
- Have libxrandr-dev installed.
- Have libxinerama-dev installed.
- Have libxi-dev installed.
