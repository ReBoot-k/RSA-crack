#include <iostream>

#include "lib/RSA.cpp"

int main() {
    RSA Rsa({{"E", 493}, {"P", 23}, {"Q", 29}});
    std::vector<int> a = {298, 107, 16,  271, 237, 420,
                          298, 34,  271, 298, 107, 16};
    std::cout << Rsa.getDecryptMessage(a) << "\n";
    return 0;
}
