#include "GameEngine.h"
#include "Exceptions.h"
#include <iostream>

int main() {
    try {
        ProxyMystery::GameEngine engine("data/case_config.txt", "data/case_archive.txt");
        engine.startGame();
    } catch (const ProxyMystery::ProxyGameException& e) {
        std::cerr << "\n[Fatal Game Exception]: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "\n[Fatal System Exception]: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "\n[Fatal Unknown Exception caught at main]\n";
        return 1;
    }

    return 0;
}
