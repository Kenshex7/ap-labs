// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"os"
	"math/rand"
	"strconv"
	"time"
)

type Point struct{ x, y float64 }

// A Path is a journey connecting the points with straight lines.

func (p Point) X() float64{
	return p.x
}

func (p Point) Y() float64{
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}
//!-point
//!+path
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	fmt.Print("   - ")
	for i := range path {
		if i > 0 {
			fmt.Print(path[i-1].Distance(path[i]), " + ")
			sum += path[i-1].Distance(path[i])
		}
	}
	fmt.Print(path[len(path) - 1].Distance(path[0]))
	sum += path[len(path) - 1].Distance(path[0])
	fmt.Print(" = ")
	return sum
}

//!-path

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
func onSegment(p, q, r Point) bool {
	if q.X() <= math.Max(q.X(), r.X()) && q.X() >= math.Min(q.X(), r.X()) &&
		q.Y() <= math.Max(q.Y(), r.Y()) && q.Y() >= math.Min(q.Y(), r.Y()) {
			return true;
	}
	return false;
}

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
func orientation(p, q, r Point) int{
    val := ( (q.Y() - p.Y()) * (r.X() - p.X()) - (q.X() - p.X()) * (r.Y() - q.Y()) )
	if val == 0 {
		return 0
	}
	if val > 0 {
		return 1
	} else {
		return 2
	}
} 

// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
func doIntersect(p1, q1, p2, q2 Point) bool{ 
    // Find the four orientations needed for general and 
    // special cases 
    o1 := orientation(p1, q1, p2)
    o2 := orientation(p1, q1, q2) 
    o3 := orientation(p2, q2, p1) 
    o4 := orientation(p2, q2, q1) 
  
    // General case 
    if o1 != o2 && o3 != o4 {	
        return true
    }
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if o1 == 0 && onSegment(p1, p2, q1){
    	return true 
    }   
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if o2 == 0 && onSegment(p1, q2, q1){
    	return true 
    }
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if o3 == 0 && onSegment(p2, p1, q2){
    	return true 
    } 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if o4 == 0 && onSegment(p2, q1, q2){
    	return true 
    }
  
    return false // Doesn't fall in any of the above cases 
} 

func main(){
	if len(os.Args) < 2 {
		fmt.Printf("How to compile: ./geometry <number>\n")
	}
	numSides, error := strconv.Atoi(os.Args[1])
	if error == nil {
    	fmt.Printf("- Generating a [%v] sides figure\n", numSides)
	}
	Paths := make(Path, numSides)
	Paths = genVertices(Paths, numSides)
	for doIntersect(Paths[0], Paths[1], Paths[2], Paths[3]) {
		Paths = genVertices(Paths, numSides)
	}
	fmt.Printf("- Figure's Perimeter\n")
	fmt.Println(Paths.Distance())

}

func genVertices (Paths Path, sides int) []Point {
	for i := 0; i < sides; i++ {
    Paths[i].x = (genRange(-100, 100))
    Paths[i].y = (genRange(-100, 100))
    fmt.Println("   - ( ", Paths[i].X(), ", ", Paths[i].Y(), ")")
  }
	return Paths
}

func genRange(min, max int ) float64 {
	seed := rand.NewSource(time.Now().UnixNano())
	rand := rand.New(seed)
	return rand.Float64()*float64((max - min) + min)
}