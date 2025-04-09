#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

/*
Kendra Winhall 
Neighbor Finder Lab, CS 361
Adapted from starter code from Anya Vostinar

This program depicts a cell (black) and its neighbors (red) moving across a toroidal grid.
*/

emp::web::Document doc{"target"};

// Defines the animation of a cell and its neighbors moving across a toroidal grid
class NFAnimator : public emp::web::Animate {
    int cellLength = 30; // cell length in pixels
    int numRowCells = 10; // number of cells in the square grid per row/column
    double gridLength = (double)numRowCells * cellLength; // grid length in pixels
    emp::web::Canvas canvas{gridLength, gridLength, "canvas"};

    public: 
        int currentX = 0; // x coordinate of current cell
        int currentY = 0; // y coordinate of current cell
        NFAnimator() {
            makeGrid();
            doc << canvas;
            doc << GetToggleButton("Toggle");
            doc << GetStepButton("Step");
        }

        // Makes a square grid with white cells and black lines
        void makeGrid() {
            for (int x = 0; x < numRowCells; x++) {
                for (int y = 0; y < numRowCells; y++) {
                    canvas.Rect(x*cellLength, y*cellLength, cellLength, cellLength, "white", "black");
                }
            }
        }

        // Colors the current cell black and its toroidal Moore neighborhood red
        void FindNeighbors(int x, int y) {
            makeGrid(); // wipes previous cell/neighbor coloration from grid

            // finds current cell's toroidal Moore neighborhood
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    int neighborX = emp::Mod(a+x, numRowCells);
                    int neighborY = emp::Mod(b+y, numRowCells);
                    if (a == 0 and b == 0) { // colors current cell black
                        canvas.Rect(x*cellLength, y*cellLength, cellLength, cellLength, "black", "black");
                    }
                    else { // colors neighbors red
                        canvas.Rect(neighborX*cellLength, neighborY*cellLength, cellLength, cellLength, "red", "black");
                    }
                }
            }
        }

        // Creates the animation, which is a cell and its neighbors moving across the toroidal grid
        void DoFrame() override {
            FindNeighbors(currentX, currentY); // colors current cell and its neighbors

            // computes the cell coordinates for the next frame
            if (currentY % 2 == 0) {
                if (currentX == numRowCells - 1) {
                    currentY++;
                }
                else {
                    currentX++;
                }
            }
            else {
                if (currentX == 0) {
                    if (currentY == numRowCells - 1) {
                        currentX = 0;
                        currentY = 0;
                    }
                    else {
                        currentY++;
                    }
                }
                else {
                    currentX--;
                }
            }
        }
};

NFAnimator animator;

// Runs animation
int main() {
    animator.DoFrame();
}