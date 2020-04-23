#include <iostream>
#include <chrono>
#include <thread>

bool displayer(std::string image){

    char buffer[128];
    std::string result = "";

    FILE* pipe = popen(("display "+image+" 2>&1").c_str(), "r");
    if (!pipe) {
        std::cout << "Error: cant access to command line." << std::endl;
        return false;
    }
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
           result += buffer;
    } catch (...) {
        pclose(pipe);
        std::cout <<"Error: problem on the bash pipeline" << std::endl;
        return false;
    }

    int g = pclose(pipe);

    return WEXITSTATUS(g) == 0;

}


int main(int argc, char *argv[]){

    std::chrono::seconds waitDuration(20*60);

    if(argc != 2){
        std::cout << "Error: start with one arguments only : relaxer \"image.jpg\"" << std::endl;
        return 1;
    }

    std::string image(argv[1]);

    while(true){

        std::this_thread::sleep_for(waitDuration);

        if(!displayer(image)){
            std::this_thread::sleep_for(waitDuration);
            return 0;
        }
    }

}
