/*
* Parent class for all functions which will display to the screen,
* adds essential control for this
*/

#ifndef _DISPLAY_H
#define _DISPLAY_H



class Display {
    private:
    int num_of_options;

    public:
    void RefreshScreen(void);
    void ClearScreen(void);
    void PauseProgram(void);
    void DisplayHeader(void);
};

#endif