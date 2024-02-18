#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>

#include "RSA.hpp"
using boost::multiprecision::cpp_int;

void RSA::_initValues() {
    E = &options["E"];
    N = &options["N"];
    D = &options["D"];
    P = &options["P"];
    Q = &options["Q"];
    PHI = &options["PHI"];
}

std::vector<std::pair<int, int>> RSA::_getDivisorsN() {
    const int NUMBER = N->value();
    std::vector<std::pair<int, int>> divisors;
    for (int i = 2; i <= sqrt(NUMBER); i++) {
        if (NUMBER % i == 0) {
            divisors.push_back(std::make_pair(i, NUMBER / i));
        }
    }

    if (divisors.empty()) {
        std::cerr << "[X] No found divisors for " << NUMBER << "\n";
        exit(1);
    }
    return divisors;
}

int RSA::_getD() {
    int D = 0;
    while (D * E->value() % PHI->value() != 1) {
        D++;
    }

    return D;
}

void RSA::_calibrateValues() {
    if (!*E) {
        std::cerr << "[X] E missing!\n";
        exit(1);
    }

    if (*PHI && (*P && !*Q)) {
        *Q = PHI->value() / (P->value() - 1) + 1;
    }

    if (*PHI && (!*P && *Q)) {
        *P = PHI->value() / (Q->value() - 1) + 1;
    }

    if (*N && (!*P && !*Q)) {
        bool isFound = false;
        std::vector<std::pair<int, int>> divisors = _getDivisorsN();

        if (!(*P && *Q)) {
            std::tie(*P, *Q) = divisors[0];
            isFound = true;
        } else {
            for (const auto divisor : divisors) {
                if (divisor.first == P->value() ||
                    divisor.first == Q->value() ||
                    divisor.second == P->value() ||
                    divisor.second == Q->value()) {
                    std::tie(*P, *Q) = divisor;
                    isFound = true;
                    break;
                }
            }
        }
        if (!isFound) {
            std::cerr << "[X] Not found divisors\n";
            exit(1);
        }
    }

    if (!*N) {
        *N = P->value() * Q->value();
    }

    if (!*PHI) {
        *PHI = (P->value() - 1) * (Q->value() - 1);
    }

    if (!*D) {
        *D = _getD();
    }
}

RSA::RSA(const std::map<std::string, std::optional<int>>& parametrs) {
    setOptions(parametrs);
};

std::string RSA::getDecryptMessage(const std::vector<int>& encrypt) {
    std::string decrypt = "";
    for (cpp_int element : encrypt) {
        cpp_int symbol = element;
        for (int i = 0; i < D->value() - 1; i++) {
            symbol *= element;
        }

        symbol %= N->value();
        decrypt += static_cast<char>(symbol);
    }
    return decrypt;
}

void RSA::setOptions(
    const std::map<std::string, std::optional<int>>& parametrs) {
    options = {{"E", std::nullopt}, {"N", std::nullopt}, {"D", std::nullopt},
               {"P", std::nullopt}, {"Q", std::nullopt}, {"PHI", std::nullopt}};

    for (auto& option : options) {
        auto it = parametrs.find(option.first);
        if (it != parametrs.end()) {
            option.second = it->second;
        }
    }

    _initValues();
    _calibrateValues();
}
