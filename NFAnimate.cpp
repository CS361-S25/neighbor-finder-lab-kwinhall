#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

emp::web::Document doc{"target"};

class NFAnimator : public emp::web::Animate {
    emp::web::Canvas canvas{100, 100, "canvas"};
    int squareSize = 10;

    public: 

        NFAnimator() {
            for (int x = 0; x < 10*squareSize; x+=squareSize) {
                for (int y = 0; y < 10*squareSize; y+=squareSize) {
                    canvas.Rect(x, y, squareSize, squareSize, "white", "black");
                }
            }
            doc << canvas;
        }

        void FindNeighbors(int x, int y) {
            for (int a = -1*squareSize; a < 2*squareSize; a+=squareSize) {
                for (int b = -1*squareSize; b < 2*squareSize; b+=squareSize) {
                    int neighborX = emp::Mod(a+x, 10*squareSize);
                    int neighborY = emp::Mod(b+y, 10*squareSize);
                    canvas.Rect(neighborX, neighborY, squareSize, squareSize, "red", "black");
                }
            }
            canvas.Rect(x, y, squareSize, squareSize, "black", "black");
        }
};

NFAnimator animator;

int main() {
    animator.Step();
    animator.FindNeighbors(0,0);
}