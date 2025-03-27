# DoG - A C++/OpenCV approach on the Extended Difference of Gaussians Filter

## Features
- Application of the Difference of Gaussians Filter on an image followed by a tanh thresholding.
- OOP structured C++ code.
- Grayscale or colored implementation of the filter.
- Support to a great variety of image formats(e.g: .png, .jpg, etc.).
- Modularity: make your thresholding function or change the blur algorithm, have fun!

## Requirements
``g++ >= 13.0.0 && opencv >= 4.6.0``

## How can I run it?
- clone the repository using:

``git clone https://github.com/LimaLuckas/DoG.git``

- go to src:
``cd src ``

- run the following commands (CMake implementation soon):
``g++ main.cpp dogFilter.cpp -o main  $(pkg-config --cflags --libs opencv4)``

``./main``

Inspired and based on Winnemöller, Kyprianidis and Olsen (2012) research of the Difference of Gaussians Filter. [Link to the article.](https://users.cs.northwestern.edu/~sco590/winnemoeller-cag2012.pdf)

This code is under the MIT License. [About the MIT License.](https://opensource.org/license/mit)
