//Made by S.H.G

#include <SFML/Graphics.hpp>
#include "LinearSearch.h"
#include "BinarySearch.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Stacks.h"
#include "Queue.h"
#include "Queue.cpp"
#include "LinkedList.h"
#include "AVLtree.h"
#include "AVLtree.cpp"
#include "Dijkstra.h"
#include "Maze.h"
#include "Maze.cpp"
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace sf;
using namespace std;

const int windowWidth = 1366;
const int windowHeight = 712; //708 704 712

pair<RectangleShape, Text> createButton(
    const Font& font,
    const string& text,
    const Vector2f& position,
    const Color& buttonColor,
    const Color& textColor,
    unsigned int charSize
) {
    //create the button
    RectangleShape button(Vector2f(200,40));
    button.setFillColor(buttonColor);
    button.setPosition(static_cast<int>(position.x), static_cast<int>(position.y));
    //button text
    Text buttonText;
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(charSize);
    buttonText.setFillColor(textColor);
    buttonText.setPosition(
        button.getPosition().x + 40,
        button.getPosition().y + 7
    );

    //center the button text
    FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(
        static_cast<int>(textBounds.left + textBounds.width / 2), 
        static_cast<int>(textBounds.top + textBounds.height / 2)
    );
    buttonText.setPosition(
        static_cast<int>(button.getPosition().x + button.getSize().x / 2), //center horizontally
        static_cast<int>(button.getPosition().y + button.getSize().y / 2) //center vertically
    );

    return {button, buttonText};
}

Text setText(const Font& font, unsigned int charSize, const Color& textColor) {
    Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(charSize);
    displayText.setFillColor(textColor);
    return displayText;
}

void visualizeLinearSearch(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0));
    vector<int> elements(30);
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 51; //random element from 1 to 50
    }

    string input = "";
    string resultText = "Enter target number";
    string complexity = "";
    bool searching = false;
    vector<int> targetIndexes = {};

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if(event.type == Event::TextEntered) {
                if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                } else if(event.text.unicode == '\r') {
                    searching = true; //if user presses "Enter" key, start searching
                } else if(isdigit(event.text.unicode)) {
                    input += static_cast<char>(event.text.unicode); //add digit to input
                }
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if (searching) {
            int target = stoi(input); //convert input to a number
            input = "";
            complexity = "Time complexity: O(n) \nSpace complexity: O(1)";
            targetIndexes = linearSearch(elements, target);
            if(targetIndexes.size() != 0) {
                if(targetIndexes.size() > 1) {
                    resultText = "Found " + to_string(target) + " at indexes ";
                    for(int i=0; i < targetIndexes.size(); ++i) {
                        resultText += to_string(targetIndexes[i]);
                        if(i < targetIndexes.size() - 1) {
                            resultText += " & ";
                        }
                    }
                } else {
                    resultText = "Found " + to_string(target) + " at index " + to_string(targetIndexes[0]);
                }
            } else {
                resultText = "Element " + to_string(target) + " not found.";
            }
            searching = false; //reset for next search
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 22; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display first instruction (and results after first search)
        displayText.setString(resultText + "\nTarget: " + input);
        displayText.setPosition(50, 150);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeBinarySearch(RenderWindow& window, Font& font, Font& menuButtonFont) {
    vector<int> elements = generateUniqueNumbers(40, 1, 50);

    string input = "";
    string resultText = "Enter target number";
    string complexity = "";
    bool searching = false;
    int index;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered) {
                if(event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                } else if (event.text.unicode == '\r') {
                    searching = true; //if user presses "Enter" key, start searching
                } else if (isdigit(event.text.unicode)) {
                    input += static_cast<char>(event.text.unicode); //add digit to input
                }
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if (searching) {
            int target = stoi(input); //convert input to a number
            input = "";
            complexity = "Time complexity: O(log n) \nSpace complexity: O(1)";
            index = binarySearch(elements, target);
            if(index != -1) {
                resultText = "Found " + to_string(target) + " at index " + to_string(index);
            } else {
                resultText = "Element " + to_string(target) + " not found.";
            }
            searching = false; //reset for next search
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 22; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display first instruction (and results after first search)
        displayText.setString(resultText + "\nTarget: " + input);
        displayText.setPosition(50, 150);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeBubbleSort(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0)); //get a different number each time
    vector<int> elements(60);
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 101; //random element from 1 to 100
    }

    string startText = "Press Enter to sort.";
    string complexity = "";
    bool sorting = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered && event.text.unicode == '\r') {
                    sorting = true; //if user presses "Enter" key, start sorting
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(sorting) {
            complexity = "Time complexity\nBest: O(n)\nAverage & Worst: O(n^2) \nSpace complexity: O(1)";
            bubbleSort(elements);
            startText = "Elements sorted.";
            sorting = false;
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 21; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display starting text and text after sorting
        displayText.setString(startText);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 350);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeSelectionSort(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0)); //get a different number each time
    vector<int> elements(60);
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 101; //random element from 1 to 100
    }

    string startText = "Press Enter to sort.";
    string complexity = "";
    bool sorting = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered && event.text.unicode == '\r') {
                    sorting = true; //if user presses "Enter" key, start sorting
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(sorting) {
            complexity = "Time complexity\nBest, Average & Worst: O(n^2) \nSpace complexity: O(1)";
            selectionSort(elements);
            startText = "Elements sorted.";
            sorting = false;
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 21; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display starting text and text after sorting
        displayText.setString(startText);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 350);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeInsertionSort(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0)); //get a different number each time
    vector<int> elements(60);
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 101; //random element from 1 to 100
    }

    string startText = "Press Enter to sort.";
    string complexity = "";
    bool sorting = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered && event.text.unicode == '\r') {
                    sorting = true; //if user presses "Enter" key, start sorting
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(sorting) {
            complexity = "Time complexity\nBest: O(n)\nAverage & Worst: O(n^2) \nSpace complexity: O(1)";
            insertionSort(elements);
            startText = "Elements sorted.";
            sorting = false;
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 21; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display starting text and text after sorting
        displayText.setString(startText);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 350);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeMergeSort(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0)); //get a different number each time
    vector<int> elements(60);
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 101; //random element from 1 to 100
    }

    string startText = "Press Enter to sort.";
    string complexity = "";
    bool sorting = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered && event.text.unicode == '\r') {
                    sorting = true; //if user presses "Enter" key, start sorting
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(sorting) {
            complexity = "Time complexity\nBest, Average & Worst: O(n log(n)) \nSpace complexity: O(n)";
            mergeSort(elements);
            startText = "Elements sorted.";
            sorting = false;
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 21; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display starting text and text after sorting
        displayText.setString(startText);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 350);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeQuickSort(RenderWindow& window, Font& font, Font& menuButtonFont) {
    srand(time(0)); //get a different number each time
    vector<int> elements(60);
    int n = elements.size();
    for(int i=0; i < elements.size(); ++i) {
        elements[i] = 1 + rand() % 101; //random element from 1 to 100
    }

    string startText = "Press Enter to sort.";
    string complexity = "";
    bool sorting = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered && event.text.unicode == '\r') {
                    sorting = true; //if user presses "Enter" key, start sorting
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(sorting) {
            complexity = "Time complexity\nBest & Average:O(n log(n))\nWorst: O(n^2) \nSpace complexity: O(log(n))";
            quickSort(elements, 0, n - 1);
            startText = "Elements sorted.";
            sorting = false;
        }

        window.clear(Color::Black);

        //display array elements
        string arrayDisplay = "Array: ";
        int limitPerLine = 21; int counter = 0;
        for(int num : elements) {
            arrayDisplay += to_string(static_cast<int>(num)) + " | ";
            counter++;
            if(counter == limitPerLine) {
                arrayDisplay += "\n            "; //avoid going beyond screen limits
                counter = 0;
            }
        }

        displayText.setString(arrayDisplay);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display starting text and text after sorting
        displayText.setString(startText);
        displayText.setPosition(50, 250);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 350);
        window.draw(displayText);

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeStacks(RenderWindow& window, Font& font, Font& menuButtonFont) {
    Stacks stack; //initialize the stack
    string instructions = "Type any number and Enter to Push. Type P to Pop. Type T for Top.";
    string stackStatus = "";
    string topElementText = "";
    string complexity = "";
    string input = "";
    bool element_added = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered) {
                //char value = static_cast<char>(event.text.unicode);
                if(isdigit(event.text.unicode)) {
                    stackStatus = "";
                    topElementText = "";
                    input += static_cast<char>(event.text.unicode); //add digit to input
                } else if(event.text.unicode == '\r') {
                    element_added = true;
                } else if(event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                }
                else if (event.text.unicode == 'p' || event.text.unicode == 'P') {
                    if(!stack.isEmpty()) {
                        stackStatus = "Popped " + to_string(stack.top());
                        topElementText = "";
                        stack.pop();
                        input = "";
                    } else {
                        stackStatus = "Stack is empty.";
                        input = "";
                    }
                }
                else if (event.text.unicode == 't' || event.text.unicode == 'T') {
                    if (!stack.isEmpty()) {
                        topElementText = "Top: " + to_string(stack.top());
                        input = "";
                    } else {
                        stackStatus = "Stack is empty.";
                        topElementText = "Top: None";
                        input = "";
                    }
                } 
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if(element_added) {
            int number = stoi(input);
            stack.push(number);
            stackStatus = "Pushed " + to_string(number);
            input = "";
            complexity = "Time complexity:\n    Average & Worst:\n        Access: O(n)\n        Search: O(n)\n        Insertion: O(1)\n        Deletion: O(1)\n\nSpace complexity: O(n)";
            element_added = false; //reset for next push
        }

        window.clear(Color::Black);

        //display instructions
        displayText.setString(instructions);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display stack status
        displayText.setString(stackStatus + input);
        displayText.setPosition(50, 100);
        window.draw(displayText);

        //display top element
        displayText.setString(topElementText);
        displayText.setPosition(50, 150);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(900, 150);
        window.draw(displayText);

        //draw stack visualization
        int yOffset = 150; //start drawing stack below text
        int xOffest = 583;
        Node* current = stack.topNode; //access the stack's topNode

        while(current) {
            RectangleShape rectangle(Vector2f(100, 50)); //each stack element as a box
            rectangle.setFillColor(Color::Blue);
            rectangle.setOutlineColor(Color::White);
            rectangle.setOutlineThickness(2);
            rectangle.setPosition(xOffest, yOffset);

            //element text
            Text elementText;
            elementText.setFont(font);
            elementText.setCharacterSize(20);
            elementText.setFillColor(Color::White);
            elementText.setString(to_string(current->data));
            elementText.setPosition(xOffest + 10, yOffset + 10);

            window.draw(rectangle);
            window.draw(elementText);

            current = current->next; //move to next element
            yOffset += 60; //add spacing between elements
        }

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeQueue(RenderWindow& window, Font& font, Font& menuButtonFont) {
    Queue queue(10); //initialize the queue
    string instructions = "Type any number and Enter to Enqueue. Type D to Dequeue. Type P to Peek.";
    string queueStatus = "";
    string frontElementText = "";
    string timeComplexity = "";
    string spaceComplexity = "";
    string input = "";
    bool element_added = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered) {
                if (isdigit(event.text.unicode)) {
                    queueStatus = "";
                    frontElementText = "";
                    input += static_cast<char>(event.text.unicode); //add digit to input
                } else if (event.text.unicode == '\r') {
                    element_added = true;
                } else if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                } else if (event.text.unicode == 'd' || event.text.unicode == 'D') {
                    if (!queue.isEmpty()) {
                        queueStatus = "Dequeued " + to_string(queue.peek());
                        queue.dequeue();
                        input = "";
                    } else {
                        queueStatus = "Queue is empty.";
                        input = "";
                    }
                } else if (event.text.unicode == 'p' || event.text.unicode == 'P') {
                    if (!queue.isEmpty()) {
                        frontElementText = "Front: " + to_string(queue.peek());
                        input = "";
                    } else {
                        queueStatus = "Queue is empty.";
                        frontElementText = "Front: None";
                        input = "";
                    }
                }
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return; //exit function and return to menu
                }
            }
        }

        if (element_added) {
            int number = stoi(input);
            if(!queue.isFull()) {
                queue.enqueue(number);
                queueStatus = "Enqueued " + to_string(number);
                input = "";
                timeComplexity = "Time complexity:\n    Average & Worst:\n        Access: O(n)\n        Search: O(n)\n        Insertion: O(1)\n        Deletion: O(1)";
                spaceComplexity = "Space complexity: O(n)";
            } else {
                queueStatus = "Queue is full.";
                input = "";
            }
            element_added = false; //reset for next enqueue
        }

        window.clear(Color::Black);

        //display instructions
        displayText.setString(instructions);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display queue status
        displayText.setString(queueStatus + input);
        displayText.setPosition(50, 100);
        window.draw(displayText);

        //display front element
        displayText.setString(frontElementText);
        displayText.setPosition(50, 150);
        window.draw(displayText);

        //display time complexity
        displayText.setString(timeComplexity);
        displayText.setPosition(80, 400);
        window.draw(displayText);

        //display space complexity
        displayText.setString(spaceComplexity);
        displayText.setPosition(450, 400);
        window.draw(displayText);

        //draw queue visualization
        int xOffset = 80; //start drawing queue elements horizontally
        int yPosition = 250; //fixed vertical position for the queue

        if (!queue.isEmpty()) {
            for (int i = queue.front; i <= queue.rear; ++i) { //traverse the active range
                RectangleShape rectangle(Vector2f(100, 50)); //each queue element as a box
                rectangle.setFillColor(Color::Magenta);
                rectangle.setOutlineColor(Color::White);
                rectangle.setOutlineThickness(2);
                rectangle.setPosition(xOffset, yPosition);

                //element text
                Text elementText;
                elementText.setFont(font);
                elementText.setCharacterSize(20);
                elementText.setFillColor(Color::White);
                elementText.setString(to_string(queue.queue[i])); //access the element directly
                elementText.setPosition(xOffset + 10, yPosition + 10);

                window.draw(rectangle);
                window.draw(elementText);

                xOffset += 120; //add spacing between elements
            }
        }

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeLinkedList(RenderWindow& window, Font& font, Font& menuButtonFont) {
    LinkedList linkedList; //initialize the list
    string instructions = "Type any number and Enter to insert at the end of the list. Type D to delete the first node.";
    string listStatus = "";
    string input = "";
    string timeComplexity = "";
    string spaceComplexity = "";
    bool element_added = false;

    Text displayText = setText(font, 30, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);

    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::TextEntered) {
                if (isdigit(event.text.unicode)) {
                    listStatus = "";
                    input += static_cast<char>(event.text.unicode); //add digit to input
                } else if (event.text.unicode == '\r') {
                    element_added = true;
                } else if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                } else if (event.text.unicode == 'd' || event.text.unicode == 'D') {
                    //delete first node
                    linkedList.deleteFromBeginning();
                    listStatus = "Deleted first node.";
                    input = "";
                }
            }
            //menu button action
            else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
            }
        }

        if(element_added) {
            int number = stoi(input);
            linkedList.insertAtEnd(number);
            listStatus = "Inserted " + to_string(number) + " at the end of the list.";
            input = "";
            timeComplexity = "Time complexity:\n    Average & Worst:\n        Access: O(n)\n        Search: O(n)\n        Insertion: O(1)\n        Deletion: O(1)";
            spaceComplexity = "Space complexity: O(n)";
            element_added = false; //reset
        }

        window.clear(Color::Black);

        //display instructions
        displayText.setString(instructions);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display list status
        displayText.setString(listStatus + input);
        displayText.setPosition(50, 100);
        window.draw(displayText);

        //display time complexity
        displayText.setString(timeComplexity);
        displayText.setPosition(80, 400);
        window.draw(displayText);

        //display space complexity
        displayText.setString(spaceComplexity);
        displayText.setPosition(450, 400);
        window.draw(displayText);

        //draw linked list visualization
        int xOffset = 80; //start drawing nodes horizontally
        int yPosition = 250; //fixed vertical position for the nodes

        linkedNode* temp = linkedList.getHead(); //get the first node
        while (temp) {
            //draw each node as a box
            RectangleShape rectangle(Vector2f(100, 50)); 
            rectangle.setFillColor(Color::Green);
            rectangle.setOutlineColor(Color::White);
            rectangle.setOutlineThickness(2);
            rectangle.setPosition(xOffset, yPosition);

            //node text
            Text elementText;
            elementText.setFont(font);
            elementText.setCharacterSize(20);
            elementText.setFillColor(Color::White);
            elementText.setString(to_string(temp->data)); // Display node data
            elementText.setPosition(xOffset + 10, yPosition + 10);

            window.draw(rectangle);
            window.draw(elementText);

            xOffset += 120; //add spacing between nodes
            temp = temp->next; //move to the next node
        }

        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void drawTree(RenderWindow& window, AVL_Node* node, float x, float y, float xOffset, float yOffset, Font& font) {
    if (node == nullptr) return;

    float radius = 20; //radius of circles

    //draw left subtree and its connecting line
    if (node->left) {
        //calculate position of the child node
        float childX = x - xOffset;
        float childY = y + yOffset;

        //draw a line from parent to child (edge of the circles)
        Vector2f startPoint = {x, y + radius};           //bottom edge of parent circle
        Vector2f endPoint = {childX, childY - radius};   //top edge of child circle
        Vertex line[] = {
            Vertex(startPoint, Color::White),
            Vertex(endPoint, Color::White)
        };
        window.draw(line, 2, Lines);

        //recursively draw the left subtree
        drawTree(window, node->left, childX, childY, xOffset / 2, yOffset, font);
    }

    //draw right subtree and its connecting line
    if (node->right) {
        //calculate position of the child node
        float childX = x + xOffset;
        float childY = y + yOffset;

        //draw a line from parent to child (edge of the circles)
        Vector2f startPoint = {x, y + radius};           //bottom edge of parent circle
        Vector2f endPoint = {childX, childY - radius};   //top edge of child circle
        Vertex line[] = {
            Vertex(startPoint, Color::White),
            Vertex(endPoint, Color::White)
        };
        window.draw(line, 2, Lines);

        //recursively draw the right subtree
        drawTree(window, node->right, childX, childY, xOffset / 2, yOffset, font);
    }

    //draw the current node as a circle
    CircleShape circle(radius);
    circle.setFillColor(Color::Blue);
    circle.setOutlineColor(Color::White);
    circle.setOutlineThickness(2);
    circle.setPosition(x - radius, y - radius); //center the circle at (x, y)
    window.draw(circle);

    //draw the node value as text inside the circle
    Text text;
    text.setFont(font);
    text.setString(to_string(node->data));
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2); //center the text
    text.setPosition(x - 1, y - 5);
    window.draw(text);
}

void visualizeAVL(RenderWindow& window, Font& font, Font& menuButtonFont) {
    AVLTree avlTree; //initialize the tree
    string AVLStatus = "";
    string instructions = "Type any number and Enter to Insert a node.";
    string complexity = "";
    string input = "";
    bool element_added = false;
    
    //pre-made tree with sample values
    avlTree.root = avlTree.insert(avlTree.root, 10);
    avlTree.root = avlTree.insert(avlTree.root, 20);
    avlTree.root = avlTree.insert(avlTree.root, 5);
    avlTree.root = avlTree.insert(avlTree.root, 15);
    
    Text displayText = setText(font, 25, Color::White);
    //menu button
    auto[menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black,20);
    
    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            } else if(event.type == Event::TextEntered) {
                if(isdigit(event.text.unicode)) {
                    AVLStatus = "";
                    input += static_cast<char>(event.text.unicode); //add digit to input
                } else if (event.text.unicode == '\r') {
                    element_added = true;
                } else if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                }
            
            //menu button action
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if (menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
            }
        }

        if(element_added) {
            int value = stoi(input);
            avlTree.root = avlTree.insert(avlTree.root, value);
            input = "";
            complexity = "Time complexity: Average & Worst (All methods): O(log(n))        Space complexity: O(n)";
            element_added = false; //reset
        }

        window.clear(Color::Black);

        //display instructions
        displayText.setString(instructions);
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //display input
        displayText.setString(AVLStatus + input);
        displayText.setPosition(50, 100);
        window.draw(displayText);

        //display complexity
        displayText.setString(complexity);
        displayText.setPosition(50, 650);
        window.draw(displayText);

        //draw the tree
        if (avlTree.root) {
            float startX = window.getSize().x / 2.0f;  //center of the window
            float startY = 100.0f;  //starting vertical position
            float initialXOffset = window.getSize().x / 4.0f;  //initial horizontal spread
            float yOffset = 100.0f;  //vertical spacing between levels

            drawTree(window, avlTree.root, startX, startY, initialXOffset, yOffset, font);
        }

        // Draw menu button
        window.draw(menuButton);
        window.draw(menuButtonText);

        window.display();
    }
}

void visualizeDijkstra(RenderWindow& window, Font& font, Font& menuButtonFont) {
    //graph nodes with their positions
    vector<Vector2f> nodePositions = {
        {950, 200},  // A (0)
        {750, 200},  // B (1)
        {750, 300},  // C (2)
        {950, 300},  // D (3)
        {950, 500},  // E (4)
        {750, 500},  // F (5)
        {350, 300},  // G (6)
        {350, 500}   // H (7)
    };

    //graph setup (same as your Dijkstra implementation)
    int nodes = 8;
    vector<vector<pair<int, float>>> graph(nodes);
    
    //graph building
    graph[0].push_back({1, 129.74});
    graph[0].push_back({3, 51.23});
    graph[1].push_back({0, 129.74});
    graph[1].push_back({2, 49.83});
    graph[2].push_back({1, 49.83});
    graph[2].push_back({3, 128.96});
    graph[2].push_back({5, 103.45});
    graph[2].push_back({6, 200.90});
    graph[3].push_back({2, 128.96});
    graph[3].push_back({4, 94.47});
    graph[4].push_back({5, 132});
    graph[5].push_back({2, 103.45});
    graph[5].push_back({7, 198.46});
    graph[6].push_back({2, 200.90});
    graph[6].push_back({7, 103.12});
    graph[7].push_back({6, 103.12});

    int startingNode = -1, targetNode = -1;
    string instructions = "Enter starting node (0-7) and target node (0-7).";
    string graphStatus = "";
    string input = "";
    bool startNodeSelected = false;

    //visualization variables
    vector<float> distances(nodes, INF);
    vector<int> previous(nodes, -1);
    vector<CircleShape> nodeShapes(nodes);
    vector<Text> nodeTexts(nodes);

    //node shapes and texts
    for(int i = 0; i < nodes; ++i) {
        nodeShapes[i].setRadius(30);
        nodeShapes[i].setFillColor(Color::Blue);
        nodeShapes[i].setOutlineColor(Color::White);
        nodeShapes[i].setOutlineThickness(2);
        nodeShapes[i].setPosition(nodePositions[i].x - 30, nodePositions[i].y - 30);

        nodeTexts[i].setFont(font);
        nodeTexts[i].setString(to_string(i));
        nodeTexts[i].setCharacterSize(20);
        nodeTexts[i].setFillColor(Color::White);
        FloatRect textBounds = nodeTexts[i].getLocalBounds();
        nodeTexts[i].setOrigin(textBounds.width/2, textBounds.height/2);
        nodeTexts[i].setPosition(nodePositions[i].x - 1, nodePositions[i].y - 5);
    }

    Text displayText = setText(font, 25, Color::White);
    //menu button
    auto [menuButton, menuButtonText] = createButton(menuButtonFont, "Return to Menu", {1150, 650}, Color::White, Color::Black, 20);


    while(window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if(event.type == Event::TextEntered) {
                if(isdigit(event.text.unicode)) {
                    graphStatus = "";
                    input += static_cast<char>(event.text.unicode);
                } else if (event.text.unicode == '\b' && !input.empty()) {
                    input.pop_back(); //allows the user to backspace (erase a character)
                }
            }
            //Enter key pressed
            else if(event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) {
                    if (!startNodeSelected) {
                        //first input is start node
                        if (!input.empty()) {
                            startingNode = stoi(input);
                            startNodeSelected = true;
                            input.clear();
                        }
                    } else {
                        //second input is target node
                        if (!input.empty()) {
                            targetNode = stoi(input);
                            //run Dijkstra's algorithm
                            dijkstra(startingNode, targetNode, graph, distances, previous);
                            if (distances[targetNode] == INF) {
                                graphStatus = "No path exists between nodes";
                            } else {
                                string resultString = "Shortest distance: " + 
                                    to_string(distances[targetNode]) + " meters\n";
                                //trace path
                                vector<int> path;
                                for (int at = targetNode; at != -1; at = previous[at]) {
                                    path.push_back(at);
                                }
                                reverse(path.begin(), path.end());
                                
                                resultString += "Path: ";
                                for (size_t i = 0; i < path.size(); ++i) {
                                    resultString += to_string(path[i]);
                                    if (i < path.size() - 1) resultString += " -> ";
                                }
                                
                                graphStatus = resultString;
                            }
                            input.clear(); //reset
                            startNodeSelected = false;
                        }
                    }
                }
            }
            //menu button action
            if(event.type == Event::MouseButtonPressed && 
                event.mouseButton.button == Mouse::Left) {
                Vector2i mousePos = Mouse::getPosition(window);
                if(menuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    return;
                }
            }
        }

        window.clear(Color::Black);

        //draw instructions
        displayText.setString(startNodeSelected ? 
            "Enter target node (0-7)" : 
            "Enter starting node (0-7)");
        displayText.setPosition(50, 50);
        window.draw(displayText);

        //draw input
        displayText.setString(graphStatus + input);
        displayText.setPosition(50, 100);
        window.draw(displayText);

        //draw edges
        for (int i = 0; i < nodes; ++i) {
            for (const auto& edge : graph[i]) {
                int j = edge.first;
                Vertex line[] = {
                    Vertex(nodePositions[i]),
                    Vertex(nodePositions[j])
                };
                window.draw(line, 2, Lines);
            }
        }

        //draw graph nodes
        for (int i = 0; i < nodes; ++i) {
            //highlight start and target nodes
            if (i == startingNode) {
                nodeShapes[i].setFillColor(Color::Green);
            } else if (i == targetNode) {
                nodeShapes[i].setFillColor(Color::Red);
            } else {
                nodeShapes[i].setFillColor(Color::Blue);
            }
            
            window.draw(nodeShapes[i]);
            window.draw(nodeTexts[i]);
        }

        //draw menu button
        window.draw(menuButton);
        window.draw(menuButtonText);

        //display
        window.display();
    }
}

void visualizeDFS(RenderWindow& window, Maze& maze) {
    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        //solve the maze using DFS
        if (maze.solveMazeDFS(window)) {
            sleep(seconds(2));  //wait for 2 seconds after solving
            break;
        }
    }
}

void visualizeBFS(RenderWindow& window, Maze& maze) {
    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        //solve the maze using BFS
        if (maze.solveMazeBFS(window)) {
            sleep(seconds(2));  //wait for 2 seconds after solving
            break;
        }
    }
}

int main() {
    //set up SFML window
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Algorithm Visualizer Menu");
    window.setPosition(Vector2i(-8, 0));
    window.setFramerateLimit(60);

    int width = 35;
    int height = 15;
    int cellSize = 35;

    Maze maze(width, height, cellSize);

    Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        cout << "Failed to load font\n";
        return -1;
    }

    Font font1;
    if (!font1.loadFromFile("Roboto-Bold.ttf")) {
        cout << "Failed to load font\n";
        return -1;
    }

    vector<pair<RectangleShape, Text>> buttons;
    vector<string> buttonLabels = {
        "Linear Search",
        "Binary Search",
        "Bubble Sort",
        "Selection Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
        "Stacks",
        "Queue",
        "Linked List",
        "AVL Tree",
        "Dijkstra",
        "DFS",
        "BFS"
    };

    buttons.push_back(createButton(font1, buttonLabels[0], {355, 200}, Color::Magenta, Color::Black, 20)); //linear search
    buttons.push_back(createButton(font1, buttonLabels[1], {355, 250}, Color::Magenta, Color::Black, 20)); //binary search
    buttons.push_back(createButton(font1, buttonLabels[2], {583, 200}, Color::Cyan, Color::Black, 20)); //bubble sort
    buttons.push_back(createButton(font1, buttonLabels[3], {583, 250}, Color::Cyan, Color::Black, 20)); //selection sort
    buttons.push_back(createButton(font1, buttonLabels[4], {583, 300}, Color::Cyan, Color::Black, 20)); //insertion sort
    buttons.push_back(createButton(font1, buttonLabels[5], {583, 350}, Color::Cyan, Color::Black, 20)); //merge sort
    buttons.push_back(createButton(font1, buttonLabels[6], {583, 400}, Color::Cyan, Color::Black, 20)); //quick sort
    buttons.push_back(createButton(font1, buttonLabels[7], {355, 350}, Color::Green, Color::Black, 20)); //stacks
    buttons.push_back(createButton(font1, buttonLabels[8], {355, 400}, Color::Green, Color::Black, 20)); //queue
    buttons.push_back(createButton(font1, buttonLabels[9], {355, 450}, Color::Green, Color::Black, 20)); //linked list
    buttons.push_back(createButton(font1, buttonLabels[10], {811, 200}, Color::White, Color::Black, 20)); //AVL tree
    buttons.push_back(createButton(font1, buttonLabels[11], {811, 250}, Color::White, Color::Black, 20)); //Dijkstra
    buttons.push_back(createButton(font1, buttonLabels[12], {811, 300}, Color::White, Color::Black, 20)); //DFS
    buttons.push_back(createButton(font1, buttonLabels[13], {811, 350}, Color::White, Color::Black, 20)); //BFS

    while(window.isOpen()) {
        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed) {
                window.close();
            }
            
            //check for mouse click
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                //get mouse position
                Vector2i mousePos = Mouse::getPosition(window);
                for(size_t i=0; i < buttons.size(); ++i) {
                    const RectangleShape& button = buttons[i].first;
                    if(button.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
                        //call visualization functions
                        if(buttonLabels[i] == "Linear Search") {
                            visualizeLinearSearch(window, font, font1);
                        }
                        if(buttonLabels[i] == "Binary Search") {
                            visualizeBinarySearch(window, font, font1);
                        }
                        if(buttonLabels[i] == "Bubble Sort") {
                            visualizeBubbleSort(window, font, font1);
                        }
                        if(buttonLabels[i] == "Selection Sort") {
                            visualizeSelectionSort(window, font, font1);
                        }
                        if(buttonLabels[i] == "Insertion Sort") {
                            visualizeInsertionSort(window, font, font1);
                        }
                        if(buttonLabels[i] == "Merge Sort") {
                            visualizeMergeSort(window, font, font1);
                        }
                        if(buttonLabels[i] == "Quick Sort") {
                            visualizeQuickSort(window, font, font1);
                        }
                        if(buttonLabels[i] == "Stacks") {
                            visualizeStacks(window, font, font1);
                        }
                        if(buttonLabels[i] == "Queue") {
                            visualizeQueue(window, font, font1);
                        }
                        if(buttonLabels[i] == "Linked List") {
                            visualizeLinkedList(window, font, font1);
                        }
                        if(buttonLabels[i] == "AVL Tree") {
                            visualizeAVL(window, font, font1);
                        }
                        if(buttonLabels[i] == "Dijkstra") {
                            visualizeDijkstra(window, font, font1);
                        }
                        if(buttonLabels[i] == "DFS") {
                            visualizeDFS(window, maze);
                        }
                        if(buttonLabels[i] == "BFS") {
                            visualizeDFS(window, maze);
                        }
                    }
                }
            }
        }

    //clear the window
    window.clear(sf::Color::Black);

    //draw the buttons
    for(auto& button : buttons) {
        window.draw(button.first); //draw the rectangle shaped button
        window.draw(button.second); //draw the button text
    }
    
    //display the window contents
    window.display();
    }
    
    return 0;
}
