#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Función para convertir un número entero a hexadecimal 
string intToHex(unsigned long long int intDecimal) {
    string hex = "";
    if (intDecimal == 0) return "0";

    char hexChars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while (intDecimal > 0) {
        hex = hexChars[intDecimal % 16] + hex;
        intDecimal /= 16;
    }
    return hex;
}

// Función para convertir binario a hexadecimal 
string binaryToHex(string binary) {
    int pointPos = binary.find('.');

    string intPart = binary.substr(0, pointPos);
    string fracPart = pointPos != string::npos ? binary.substr(pointPos + 1) : "";

    // Conversión de la parte entera
    unsigned long long int intDecimal = stoull(intPart, nullptr, 2);
    string hexInteger = intToHex(intDecimal);

    // Conversión de la parte fraccionaria
    double fracDecimal = 0.0;
    if (!fracPart.empty()) {
        for (size_t i = 0; i < fracPart.size(); ++i) {
            if (fracPart[i] == '1') {
                fracDecimal += 1.0 / (1 << (i + 1));
            }
        }
    }

    string hexFractional = "";
    while (fracDecimal != 0.0) {
        fracDecimal *= 16;
        int fracInt = static_cast<int>(fracDecimal);
        hexFractional += (fracInt < 10) ? to_string(fracInt) : string(1, 'A' + fracInt - 10);
        fracDecimal -= fracInt;

        if (hexFractional.size() > 10) {  // Limitar a 10 dígitos
            break;
        }
    }

    return fracPart.empty() ? hexInteger : hexInteger + "." + hexFractional;
}

// Función para calcular el complemento restringido de un número binario
string restrictedComplement(string binary) {
    if (binary.empty()) return "Error: Cadena vacia";

    // El primer bit (bit de signo) se mantiene, los demás se invierten
    string complement = binary[0] == '0' ? "0" : "1";  // Mantiene el primer bit
    for (size_t i = 1; i < binary.size(); ++i) {
        complement += (binary[i] == '0') ? '1' : '0';  // Invertir bits
    }
    return complement;
}

// Función para convertir decimal a hexadecimal 
string decimalToHex(string decimal) {
    int pointPos = decimal.find('.');

    string intPart = decimal.substr(0, pointPos);
    string fracPart = pointPos != string::npos ? decimal.substr(pointPos + 1) : "";

    // Convertir la parte entera a hexadecimal
    unsigned long long int intDecimal = stoull(intPart);
    string hexInteger = intToHex(intDecimal);

    // Conversión de la parte fraccionaria
    double fracDecimal = fracPart.empty() ? 0.0 : stod("0." + fracPart);
    string hexFractional = "";

    for (int i = 0; fracDecimal != 0.0 && i < 20; ++i) {  // Limitar a 20 dígitos
        fracDecimal *= 16;
        int fracInt = static_cast<int>(fracDecimal);
        hexFractional += (fracInt < 10) ? to_string(fracInt) : string(1, 'A' + fracInt - 10);
        fracDecimal -= fracInt;
    }

    return fracPart.empty() ? hexInteger : hexInteger + "." + hexFractional;
}

// Función menú
void displayMenu() {
    cout << "\n===== Menu de Operaciones =====" << endl;
    cout << "1. Conversion de Binario a Hexadecimal" << endl;
    cout << "2. Obtener el Complemento Restringido de un Numero Binario" << endl;
    cout << "3. Conversion de Decimal a Hexadecimal" << endl;
    cout << "4. Salir" << endl;
    cout << "================================" << endl;
}

int main() {
    while (true) {
        displayMenu();
        int choice;
        cout << "Selecciona una opcion (1-4): ";
        cin >> choice;

        if (choice == 1) {
            string binary;
            cout << "Introduce el numero binario (ejemplo: 1010.101): ";
            cin >> binary;
            cout << "Hexadecimal: " << binaryToHex(binary) << endl;
        }
        else if (choice == 2) {
            string binary;
            cout << "Introduce el numero binario: ";
            cin >> binary;
            cout << "Complemento Restringido: " << restrictedComplement(binary) << endl;
        }
        else if (choice == 3) {
            string decimal;
            cout << "Introduce el numero decimal (ejemplo: 10.625): ";
            cin >> decimal;
            cout << "Hexadecimal: " << decimalToHex(decimal) << endl;
        }
        else if (choice == 4) {
            cout << "Gracias!" << endl;
            break;
        }
        else {
            cout << "Opcion invalida. Elige una opcion entre 1 y 4" << endl;
        }

        // Preguntar si el usuario desea realizar otra operación
        char again;
        cout << "Deseas realizar otra operacion? (s/n): ";
        cin >> again;
        if (again == 'n' || again == 'N') {
            cout << "Gracias!" << endl;
            break;
        }
    }

    return 0;
}
