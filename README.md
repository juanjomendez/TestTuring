Test Turing

This is a test for the Job Position: Geometry Developer

It has been made with Visual Studio 2019, and the boost libraries for geometry

Usage:
You can launch this tools with the followint syntax

TestTuring.exe (optional file.txt) index1 operation index2

- The first parameter (file) is optional: A text file containing the definition of the polygons
  If it is not provided, a default one (points.txt, included) will be used
- The second parameter is the index of the first polygon that we want to make operations with
- The third is the operation (char)
- And the last parameter is the index of the second polygon that we want to make operations with

* The definition of the polygons (in the text file) goes like this
 
 
  #poly0//name of the poly (It HAS to start with the # symbol... the rest is irrelevant)
  
  0.0, 0.0,//Coordinates of the first point
  
  0.0, 2.0,//Coordinates of the second point
  
  2.0, 2.0,//
  
  2.0, 0.0,
  
  0.0, 0.0,
  
  END//To indicate the end of the polygon... Note that the last point is the same than the first, to complete the polygon
  

Empty lines are allowed... 

* List of allowed operations:
+ Union (+)
- Difference (-)
* Intersection (*)


For example, you can do:

TestTuring.exe 0 + 1
This will create a file called result.svg with the union of the first (index 0) and the second (index 1) polygons, from the points.txt file

TestTuring anotherlistofpoints.txt 1 - 2
This will create a file called result.svg with the difference of the second and the third polygons from the custom file anotherlistofpoints.txt


Also, if everything is successfull, apart from the result.svg file (containing the result), it will create individual .svg files for each polygon defined in the .txt file
