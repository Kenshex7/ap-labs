package main

import (
	"fmt"
	"os"
	"log"
	"path/filepath"
)
type Content struct{
	Dirs int
	sLinks int
	Devs int
	Socks int
	oFiles int
}
// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	var Cont = Content{0,0,0,0,0}
	

	var eachArch=func(path string, infoX os.FileInfo, errX error) error{
		fileType:= string(os.FileMode.String(infoX.Mode())[0])
		//fmt.Println("El mode de este directorio es: ",fileType)
		switch fileType{
		case "d":
			Cont.Dirs++
		case "L":
			Cont.sLinks++
		case "S":
			Cont.Socks++
		case "D":
			Cont.Devs++
		default:
			Cont.oFiles++
		}
		//fmt.Println("El nombre del archivo en el que entre es:",infoX.Name())
		return nil
	}
	err:=filepath.Walk(dir,eachArch)
	if err!=nil{
		log.Fatal(err)
	}
	fmt.Println("Directory Scanner Tool")
	fmt.Println("+---------------+-------+")
	fmt.Println("|Path\t\t|",dir,"\t|")
	fmt.Println("+---------------+-------+")
	fmt.Println("|Directories\t|",Cont.Dirs,"\t|")
	fmt.Println("|Symbolic links\t|",Cont.sLinks,"\t|")
	fmt.Println("|Devices\t|",Cont.Devs,"\t|")
	fmt.Println("|Sockets\t|",Cont.Socks,"\t|")
	fmt.Println("|Other files\t|",Cont.oFiles,"\t|")
	fmt.Println("+---------------+-------+")



	return nil
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}

