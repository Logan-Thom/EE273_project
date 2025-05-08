/*
Parent class to handle screen operations when navigating the site
Created for: EE273 E-Commerce Project
Last Updated: 08/05/25
Updated By: Logan Thom, Jamie Briggs
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