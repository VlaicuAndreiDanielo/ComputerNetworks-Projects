#include <iostream>
#include <string>
#include <vector>

bool isBinary(const std::string& s) {
    for (char c : s) {
        if (c != '0' && c != '1')
            return false;
    }
    return true;
}

void PrintPolynomial(const std::string& generator) {
    int degree = generator.size() - 1;
    std::cout << "Generator Polynomial: ";
    for (size_t i = 0; i < generator.size(); i++) {
        if (i > 0)
            std::cout << " + ";
        int power = degree - i;
        if (generator[i] == '1') {
            if (power > 0)
                std::cout << "X^" << power;
            else
                std::cout << "1";
        }
        else {
            std::cout << "0x^" << power;
        }
    }
    std::cout << std::endl;
}

std::vector<std::string> GeneratePyramidMatrix(const std::vector<std::string>& steps, const std::string& extended_message)
{
    int rows = static_cast<int>(steps.size());
    int cols = static_cast<int>(extended_message.size());

    std::vector<std::string> matrix(rows, std::string(cols, ' '));

    for (int i = 0; i < rows; i++) {
        std::string display = steps[i];
        size_t pos = display.find_first_not_of('0');
        if (pos == std::string::npos) {
            display.clear();
        }
        else {
            display.erase(0, pos);
        }

        int d = static_cast<int>(display.size());
        if (d > cols) d = cols; 
        matrix[i].replace(cols - d, d, display);
    }

    return matrix;  
}

void PrintFullSteps(const std::vector<std::string>& steps, const std::string& extended_message)
{
    std::cout << "\nIntermediate XOR Processes:" << std::endl;
    std::cout << extended_message << std::endl;
    for (const auto& step : steps) {
        std::cout << step << std::endl;
    }
}

void PrintPyramidMatrix(const std::vector<std::string>& matrix, const std::string& extended_message)
{
    std::cout << "\nPyramid Form of Steps Matrix:\n";
    std::cout << extended_message << std::endl;

    for (const auto& row : matrix) {
        std::cout << row << std::endl;
    }
}

void PrintStepsSideBySide(const std::vector<std::string>& steps, const std::vector<std::string>& pyramidMatrix, const std::string& extended_message)
{
    size_t rowCount = std::max(steps.size(), pyramidMatrix.size());

    std::cout << "\nFull and Pyramided Steps (Side by Side):\n";
    std::cout << extended_message << "   |   " << extended_message << std::endl;
    for (size_t i = 0; i < rowCount; i++) {

        std::string stepDisplay = steps[i];
        std::cout << stepDisplay << "   |   " << pyramidMatrix[i] << std::endl;
    }
}

void PrintElements(const std::string& extended_message, const std::string& remainder, const std::string& xor_with_remainder, const std::string& final_encoded_message)
{
    std::string separation(2 * extended_message.size() + 7, '=');
    std::cout << std::endl << separation << std::endl;

    std::cout << "Extended Initial Message: " << extended_message << std::endl;
    std::cout << "Remainder After Division: " << remainder << std::endl;
    std::cout << "Final Encoded Message: " << final_encoded_message << std::endl;
    std::cout << "Final XOR Result: " << xor_with_remainder << std::endl;

    std::cout << "\nAligned Display of Remainder Under the Extended Message:\n";
    std::cout << "\n" << extended_message << "\n";
    std::string spaces(extended_message.size() - remainder.size(), ' ');
    std::cout << spaces << remainder << std::endl;
    std::string spaces2(extended_message.size(), '-');
    std::cout << spaces2 << std::endl;
    std::cout << final_encoded_message;
    std::cout << std::endl;
}

std::string XORDivision(std::string dividend, const std::string& divisor, std::vector<std::string>& steps) {
    int n = dividend.size();
    int k = divisor.size();
    std::cout << "\nPerforming XOR Processes:" << std::endl;

    for (int i = 0; i <= n - k; i++) {
        if (dividend[i] == '1') {  

            std::string currentSegment = dividend.substr(i, k);
            std::string result;
            result.reserve(k);

            for (int j = 0; j < k; j++) {
                result.push_back(((currentSegment[j] - '0') ^ (divisor[j] - '0')) + '0');
            }

            std::cout << currentSegment << " XOR " << divisor << " -> " << result << std::endl;

            for (int j = 0; j < k; j++) {
                dividend[i + j] = result[j];
            }
            steps.push_back(dividend);
        }
    }

    return dividend.substr(n - (k - 1));
}

int main() {
    std::string binaryMessage, generator;

    std::cout << "Enter the binary string: ";
    std::cin >> binaryMessage;
    std::cout << "Enter the generator polynomial:";
    std::cin >> generator;

    if (!isBinary(binaryMessage) || !isBinary(generator)) {
        std::cout << "Error: The message and the polynomial must be binary strings." << std::endl;
        return 1;
    }
    if (binaryMessage.size() <= generator.size()) {
        std::cout << "Error: The message must be longer than the generator polynomial." << std::endl;
        return 1;
    }

    PrintPolynomial(generator);

    size_t pos = generator.find_first_not_of('0');
    if (pos != std::string::npos) {
        generator = generator.substr(pos);
    }
    else {
        std::cout << "Error: Generator polynomial cannot be all zeros." << std::endl;
        return 1;
    }

    PrintPolynomial(generator);

    int degree = generator.size() - 1;

    
    std::string extendedMessage = binaryMessage;
    extendedMessage.append(degree, '0');

    std::vector<std::string> steps;
    std::string remainder = XORDivision(extendedMessage, generator, steps);

    std::string final_encoded_message = binaryMessage + remainder;

    std::string last_part = extendedMessage.substr(extendedMessage.size() - degree);
    std::string XORWithRemainder = "";
    for (int i = 0; i < degree; i++) {
        char bit = ((last_part[i] - '0') ^ (remainder[i] - '0')) + '0';
        XORWithRemainder.push_back(bit);
    }
    std::vector<std::string> pyramidMatrix = GeneratePyramidMatrix(steps, extendedMessage);

    std::cout << "\nExtended Message: " << extendedMessage << std::endl;
    std::cout << std::endl;

    PrintStepsSideBySide(steps, pyramidMatrix, extendedMessage);
    PrintElements(extendedMessage, remainder, XORWithRemainder, final_encoded_message);

    PrintFullSteps(steps, extendedMessage);
    PrintPyramidMatrix(pyramidMatrix, extendedMessage);

    return 0;
}
