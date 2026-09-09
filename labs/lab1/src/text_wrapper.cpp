#include "text_wrapper.hpp"
#include <iostream>
#include <cstring>

using namespace std;

TextWrapper::TextWrapper(const MyString  &input, int line_width):
 input_text(input), max_width(line_width), current_index(0), current_line_len(0){}

bool TextWrapper::is_end() const{
    return input_text.get(current_index) == '\0';
}

MyString TextWrapper::get_next_word(){
    while (!is_end() && input_text.get(current_index) == ' ')
    {
        current_index++;
    }
    if (is_end()) return MyString("");
    
    int cap = 10;
    int len = 0;
    char *buff = new char[cap];

    while (!is_end() && input_text.get(current_index) != ' '){
        if (len + 1 >= cap){
            cap *= 2;
            char *temp = new char[cap];
            for (int i = 0; i < len; i++) temp[i] = buff[i];
            delete[] buff;
            buff = temp;
        }
        buff[len++] = input_text.get(current_index);
        current_index++;        
    }
    buff[len] = '\0';

    MyString word(buff);
    delete[] buff;
    return word;
}

void TextWrapper::print_wrapped(){
    current_index = 0;
    current_line_len = 0;

    cout << " ";
    for (int i = 0; i < max_width; i++) cout << "-";
    cout << "\n";

    cout << "/ ";
    while (!is_end()){
        MyString word = get_next_word();
        int word_len = 0;
        while (word.get(word_len) != '\0') word_len++;


        int space_needed = (current_line_len == 0) ? 0 : 1;

        if (current_line_len + space_needed + word_len > max_width){
            for (int i = 0; i < max_width - current_line_len; i++) cout << " ";
            cout << " \\\n| ";
            current_line_len = 0;
            space_needed = 0;             
        }

        if (space_needed > 0){
            cout << " ";
            current_line_len++;
        }        

        for (int i = 0; i < word_len; i++){
            cout << word.get(i);
        }
        current_line_len += word_len;
    }

    for (int i = 0; i < max_width - current_line_len; i++) cout << " ";
    cout << " /\n";

    cout << " ";
    for (int i = 0; i < max_width; i++) cout << "-";
    cout << "\n";





    cout << "    \\\n";
    cout << "     \\\n";
    cout << "      \\\n";
    cout << "       \\\n";
    cout << "          ⣎⠉⠉⠉⠉⠉⠉⠉⠉⣱          \n";
    cout << "          ⢻        ⡏          \n";
    cout << "         ⢰⠚⠒⠒⠒⠒⠒⠒⠒⠒⠓⡆         \n";
    cout << "  ⢀⣀⣀⣀  ⢠⡤⢄⣸          ⣇⡠⢤⡄  ⣀⣀⣀⡀  \n";
    cout << " ⡰⠕  ⠐⠂⠍⡆⠙⣭⣛⡀⠤⠤⠤⠤⠤⠤⠤⠄⢐⣛⣭⠋⢰⡩⠐⠂⠐⠫⢆\n";
    cout << " ⢣⢄    ⢀⢠⢛⠞⠁  ⠉⠉⠁⠒⠒⠒⠒⠈⠉⠉  ⠈⠳⡛⡄⡀⡠⡜\n";
    cout << " ⠈⠳⣕  ⣰⣻⠋                ⠙⣝⣆  ⣪⠞  \n";
    cout << "    ⠉⢠⠇   ⣀⣀⣀      ⣀⣀⣀   ⠸⡄⠉   \n";
    cout << "    ⢸  ⢠⡾⠿⠿⠿⣿⣄  ⣠⣿⠿⠿⠿⢷⡀  ⡇    \n";
    cout << "    ⢸  ⠈⢀⣶⠛⠛⢦⠙  ⠐⠋⡶⠛⠛⣷⡀   ⡇    \n";
    cout << "    ⡸⠃  ⠸⣷⡈⡃⣸⠇  ⠸⣇⢹⠁⣾⠇  ⠘⢇    \n";
    cout << "   ⢸      ⢀⣩⠿⢿⡭⠤⢶⣶⣤⣭⡿⠿⣉⣀ ⠈⡆   \n";
    cout << "   ⠘⢆⡀⢀⡞⠁   ⠙⠛⠿⠿⠛⠋   ⠈⢳⡀ ⡰⠃   \n";
    cout << "     ⢹⢾⡄              ⢠⡗⡏     \n";
    cout << "     ⠸⡄⢷⣀     ⣠⣄     ⢀⡾⢠⠃     \n";
    cout << "      ⢣⠈⠫⣹⡒⠚⢉⠉⢉⡉⠉⣉⠓⢒⣏⠝⠁⡞      \n";
    cout << "       ⠳⡀⠈⠙⠒⠛⠤⠼⠧⠤⠛⠒⠋⠁⣀⠞⠁      \n";
    cout << "        ⠈⠓⠦⠤⣤⣀⣠⣄⣀⣠⠤⠴⠚⠁        \n";
    cout.flush();

}

