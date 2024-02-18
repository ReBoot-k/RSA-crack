#pragma once

#include <map>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class RSA {
   private:
    std::map<std::string, std::optional<int>> options;

    std::optional<int>*E, *N, *D, *P, *Q, *PHI;

    void _initValues();

    std::vector<std::pair<int, int>> _getDivisorsN();
    int _getD();
    void _calibrateValues();

   public:
    RSA(const std::map<std::string, std::optional<int>>& parametrs);
    void setOptions(const std::map<std::string, std::optional<int>>& parametrs);
    std::string getDecryptMessage(const std::vector<int>& encrypt);
};
