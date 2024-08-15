#include "../ifconfig/ifconfig.hpp"
#include <iostream>

int main() {

    std::cout << ifconfig::get_interface().addr_ipv4 << std::endl;
}