#ifndef ODEFUNCTION_H
#define ODEFUNCTION_H

#include <vector>
#include <string>
#include <algorithm>

class OdeFunction {
    std::vector<double> constants;

    int numberOfApostrophes(const std::string &str) {
        int cnt = 0;
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] == 'y') {
                while (str[++i] == '\'')
                    cnt++;
                break;
            }
        }
        return cnt;
    }


bool foundCoef(char sign){
  return sign == '=' || sign == '+' || sign == '-';
}

int evaluateSign(char sign){
  return sign == '+' or sign == '=' ? 1 : -1;
}

double getCoef(std::string &equation, std::string &derivation){
  size_t startPos = equation.find(derivation);

  if(startPos == std::string::npos){
    return 0;
  }

  equation.replace(startPos, derivation.length(), "");

  std::string coef;
  int i = startPos - 1;
  for(; !foundCoef(equation[i]); i--){
    coef.push_back(equation[i]);
  }

  std::reverse(coef.begin(), coef.end());
 
  return evaluateSign(equation[i]) * std::stod(coef);
}


public:
    OdeFunction(std::string equation) {
      constants.resize(numberOfApostrophes(equation) + 1);
      std::vector<std::string> derivations(prepareDerivations(constants.size() - 1));
      for(char &c : equation){
        if(c != '='){
          c = ' ';
        } else 
            break;
      }
      for(int i = constants.size() - 1; i >= 0; i--){
        constants[i] = getCoef(equation, derivations[i]);
       }
    }

    // OdeFunction(std::vector<double> consta) : constants(consta) {}

    double operator()(std::vector<double> var) {
        double sum = 0;
        for (int i = 0; i < constants.size(); i++)
            sum += constants[i] * var[i];
        return sum;
    }

    double operator()(double var) {
        return constants[0] * var;
    }

    int sysOrder() {
        return constants.size();
    }


    std::vector<std::string> prepareDerivations(int sysOrder){
      std::vector<std::string> derivations(sysOrder);
        int i = 0;
        for(std::string &subString : derivations){
          subString = "y";
          for(int j = 0; j < i; j++)
              subString += "'";
          i++;
        }    
        derivations.push_back("u");
      return derivations;
    }

    std::vector<double> getConstants(){
        return constants;
    }
};

#endif
