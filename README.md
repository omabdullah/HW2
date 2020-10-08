# HW2

PSID: 1838738 Osama Abdullah

The objective of this assignment is to use the GLUT library for OpenGL to create three 3D scenes, two of which will replicate the examples given in the reading document while the third scene will be from scratch based on what was learned from the assignment.

The environment we will be using for this assignment is Windows, while using Visual Studio as the IDE. The code can be compiled from Visual Studio properly after properly installing the proper dependencies, in this casing being GLUT. 

Should you not have GLUT installed properly, you can follow this video: https://www.youtube.com/watch?v=8p76pJsUP44

After GLUT is installed, you can simply compile the code and use the spacebar to cycle between the three scenes and press q (non-case sensitive) or escape to exit the program.

The first scene displays a spiral of 10 teapots, which are placed exactly 36 degrees apart using a for loop in order to form an equal circle (360 / 10 = 36). Within the for loop, each teapot is rotated the exact angle it should be placed at based on the incrementation of the for loop and properly distanced from the center using glTranslateF.

![Scene1](https://i.imgur.com/qCdUfVu.png "Scene 1")


The second scene is a pyramid of teapots, which is created through two for loops, first first for loop is the amount of rows, while the second for loop is the amount of teapots per row. Using this method, we can properly assign the correct amount of teapots per row, the first row will include 1 teapot, the second will include 2 teapots, etc. In order to achieve the pyramid design, two variables are created: spacing and height. Initially, spacing and height will be at 0 and 1 respectively until the row for loop is ran a total of 6 times to create 6 rows. For example, the first row consisting of one teapot will be placed at (0 + 1 (teapot + spacing), 1 (height), 0 (z coordinate)). After this, the spacing and height will be adjusted as such: 0 (spacing) = 0 (spacing) - 1.0 / 2.0, creating a new spacing value of -0.5, which allows the teapots to start off -0.5 units rather than at 0 initially to begin forming a pyramid shapeform. As aforementioned, height will also be adjusted to move the teapots down to create a new row and prevent overlapping on the same row through the following: 1 (height) = 1 (height) - 0.5, creating a new height value of 0.5, moving the row down to 0.5 rather than 1. This process continues until a total of 6 rows are created.

![Scene2](https://i.imgur.com/FN4tXKa.png "Scene 2")


The third scene is simply a representation of a house using solid cubes for the body, window, and chimney, a cone for the roof, and a spiral of teapots to depict the sun. The "sun" is simply the first scene, but in this case it lacks glTranslatef, causing the teapots to overlap one another.

![Scene3](https://i.imgur.com/cBT141O.png "Scene 3")


We were asked to complete the keyboard function to cycle between the scene ands properly exit the program using select keys. In this case, space was selected as the key to cycle between the scenes. This works by incrementing curProblem until it reaches 3, in which case it will reset curProblem back to 1. To exit the program, simply press q, Q, or escape and it will promptly terminate the program.

![Result](https://i.imgur.com/AySuecZ.gif "Result")

References: 
https://www.youtube.com/watch?v=8p76pJsUP44
https://www.khronos.org/registry/OpenGL-Refpages/es1.1/xhtml/
https://www.opengl.org/resources/libraries/glut/spec3/node113.html
